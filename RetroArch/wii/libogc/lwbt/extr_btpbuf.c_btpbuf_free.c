#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct pbuf {scalar_t__ ref; scalar_t__ flags; struct pbuf* next; } ;

/* Variables and functions */
 scalar_t__ PBUF_FLAG_POOL ; 
 scalar_t__ PBUF_FLAG_REF ; 
 scalar_t__ PBUF_FLAG_ROM ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct pbuf*) ; 
 int /*<<< orphan*/  btmemr_free (struct pbuf*) ; 
 int /*<<< orphan*/  pool_pbufs ; 
 int /*<<< orphan*/  rom_pbufs ; 

u8_t btpbuf_free(struct pbuf *p)
{
	u8_t cnt;
	u32 level;
	struct pbuf *q;

	if(p==NULL) return 0;

	cnt = 0;

	_CPU_ISR_Disable(level);
	while(p!=NULL) {
		p->ref--;
		if(p->ref==0) {
			q = p->next;
			if(p->flags==PBUF_FLAG_POOL) {
				btmemb_free(&pool_pbufs,p);
			} else if(p->flags==PBUF_FLAG_ROM || p->flags==PBUF_FLAG_REF) {
				btmemb_free(&rom_pbufs,p);
			} else {
				btmemr_free(p);
			}
			cnt++;
			p = q;
		} else
			p = NULL;
	}
	_CPU_ISR_Restore(level);

	return cnt;
}