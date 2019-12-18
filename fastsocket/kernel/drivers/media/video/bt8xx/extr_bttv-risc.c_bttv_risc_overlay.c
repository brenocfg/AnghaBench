#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int height; int top; int left; int width; } ;
struct bttv_overlay {int nclips; TYPE_4__ w; int /*<<< orphan*/  clips; } ;
struct bttv_format {int depth; } ;
struct TYPE_6__ {int bytesperline; } ;
struct TYPE_7__ {TYPE_2__ fmt; scalar_t__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  pci; } ;
struct bttv {scalar_t__ opt_vcr_hack; TYPE_3__ fbuf; TYPE_1__ c; } ;
struct btcx_skiplist {int start; int end; } ;
struct btcx_riscmem {int size; int /*<<< orphan*/ * cpu; int /*<<< orphan*/ * jmp; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int BT848_FIFO_STATUS_FM1 ; 
 int BT848_RISC_EOL ; 
 int BT848_RISC_SKIP ; 
 int BT848_RISC_SOL ; 
 int BT848_RISC_SYNC ; 
 int BT848_RISC_WRITE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VCR_HACK_LINES ; 
 int /*<<< orphan*/  btcx_calc_skips (int,int,int*,struct btcx_skiplist*,unsigned int*,int /*<<< orphan*/ ,int) ; 
 int btcx_riscmem_alloc (int /*<<< orphan*/ ,struct btcx_riscmem*,int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct btcx_skiplist*) ; 
 struct btcx_skiplist* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bttv_risc_overlay(struct bttv *btv, struct btcx_riscmem *risc,
		  const struct bttv_format *fmt, struct bttv_overlay *ov,
		  int skip_even, int skip_odd)
{
	int dwords, rc, line, maxy, start, end;
	unsigned skip, nskips;
	struct btcx_skiplist *skips;
	__le32 *rp;
	u32 ri,ra;
	u32 addr;

	/* skip list for window clipping */
	if (NULL == (skips = kmalloc(sizeof(*skips) * ov->nclips,GFP_KERNEL)))
		return -ENOMEM;

	/* estimate risc mem: worst case is (1.5*clip+1) * lines instructions
	   + sync + jump (all 2 dwords) */
	dwords  = (3 * ov->nclips + 2) *
		((skip_even || skip_odd) ? (ov->w.height+1)>>1 :  ov->w.height);
	dwords += 4;
	if ((rc = btcx_riscmem_alloc(btv->c.pci,risc,dwords*4)) < 0) {
		kfree(skips);
		return rc;
	}

	/* sync instruction */
	rp = risc->cpu;
	*(rp++) = cpu_to_le32(BT848_RISC_SYNC|BT848_FIFO_STATUS_FM1);
	*(rp++) = cpu_to_le32(0);

	addr  = (unsigned long)btv->fbuf.base;
	addr += btv->fbuf.fmt.bytesperline * ov->w.top;
	addr += (fmt->depth >> 3)          * ov->w.left;

	/* scan lines */
	for (maxy = -1, line = 0; line < ov->w.height;
	     line++, addr += btv->fbuf.fmt.bytesperline) {
		if ((btv->opt_vcr_hack) &&
		     (line >= (ov->w.height - VCR_HACK_LINES)))
			continue;
		if ((line%2) == 0  &&  skip_even)
			continue;
		if ((line%2) == 1  &&  skip_odd)
			continue;

		/* calculate clipping */
		if (line > maxy)
			btcx_calc_skips(line, ov->w.width, &maxy,
					skips, &nskips, ov->clips, ov->nclips);

		/* write out risc code */
		for (start = 0, skip = 0; start < ov->w.width; start = end) {
			if (skip >= nskips) {
				ri  = BT848_RISC_WRITE;
				end = ov->w.width;
			} else if (start < skips[skip].start) {
				ri  = BT848_RISC_WRITE;
				end = skips[skip].start;
			} else {
				ri  = BT848_RISC_SKIP;
				end = skips[skip].end;
				skip++;
			}
			if (BT848_RISC_WRITE == ri)
				ra = addr + (fmt->depth>>3)*start;
			else
				ra = 0;

			if (0 == start)
				ri |= BT848_RISC_SOL;
			if (ov->w.width == end)
				ri |= BT848_RISC_EOL;
			ri |= (fmt->depth>>3) * (end-start);

			*(rp++)=cpu_to_le32(ri);
			if (0 != ra)
				*(rp++)=cpu_to_le32(ra);
		}
	}

	/* save pointer to jmp instruction address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * sizeof(*risc->cpu) > risc->size);
	kfree(skips);
	return 0;
}