#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {long len; scalar_t__ data; } ;
union outputArgs {TYPE_3__ coda_ioctl; } ;
struct CodaFid {int dummy; } ;
struct TYPE_4__ {unsigned int cmd; long len; char* data; struct CodaFid VFid; } ;
union inputArgs {TYPE_1__ coda_ioctl; } ;
struct super_block {int dummy; } ;
struct TYPE_5__ {long in_size; long out_size; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct PioctlData {TYPE_2__ vi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_FREE (union inputArgs*,int) ; 
 int /*<<< orphan*/  CODA_IOCTL ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ INSIZE (int /*<<< orphan*/ ) ; 
 int PIOCPARM_MASK ; 
 long SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPARG (int /*<<< orphan*/ ) ; 
 long VC_MAXDATASIZE ; 
 int VC_MAXMSGSIZE ; 
 int /*<<< orphan*/  coda_f2s (struct CodaFid*) ; 
 int coda_upcall (int /*<<< orphan*/ ,long,int*,union inputArgs*) ; 
 int /*<<< orphan*/  coda_vcp (struct super_block*) ; 
 scalar_t__ copy_from_user (char*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  ioctl ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 

int venus_pioctl(struct super_block *sb, struct CodaFid *fid,
		 unsigned int cmd, struct PioctlData *data)
{
        union inputArgs *inp;
        union outputArgs *outp;  
	int insize, outsize, error;
	int iocsize;

	insize = VC_MAXMSGSIZE;
	UPARG(CODA_IOCTL);

        /* build packet for Venus */
        if (data->vi.in_size > VC_MAXDATASIZE) {
		error = -EINVAL;
		goto exit;
        }

        if (data->vi.out_size > VC_MAXDATASIZE) {
		error = -EINVAL;
		goto exit;
	}

        inp->coda_ioctl.VFid = *fid;
    
        /* the cmd field was mutated by increasing its size field to
         * reflect the path and follow args. We need to subtract that
         * out before sending the command to Venus.  */
        inp->coda_ioctl.cmd = (cmd & ~(PIOCPARM_MASK << 16));	
        iocsize = ((cmd >> 16) & PIOCPARM_MASK) - sizeof(char *) - sizeof(int);
        inp->coda_ioctl.cmd |= (iocsize & PIOCPARM_MASK) <<	16;	
    
        /* in->coda_ioctl.rwflag = flag; */
        inp->coda_ioctl.len = data->vi.in_size;
        inp->coda_ioctl.data = (char *)(INSIZE(ioctl));
     
        /* get the data out of user space */
        if ( copy_from_user((char*)inp + (long)inp->coda_ioctl.data,
			    data->vi.in, data->vi.in_size) ) {
		error = -EINVAL;
	        goto exit;
	}

	error = coda_upcall(coda_vcp(sb), SIZE(ioctl) + data->vi.in_size,
			    &outsize, inp);

        if (error) {
	        printk("coda_pioctl: Venus returns: %d for %s\n", 
		       error, coda_f2s(fid));
		goto exit; 
	}

	if (outsize < (long)outp->coda_ioctl.data + outp->coda_ioctl.len) {
		error = -EINVAL;
		goto exit;
	}
        
	/* Copy out the OUT buffer. */
        if (outp->coda_ioctl.len > data->vi.out_size) {
		error = -EINVAL;
		goto exit;
        }

	/* Copy out the OUT buffer. */
	if (copy_to_user(data->vi.out,
			 (char *)outp + (long)outp->coda_ioctl.data,
			 outp->coda_ioctl.len)) {
		error = -EFAULT;
		goto exit;
	}

 exit:
	CODA_FREE(inp, insize);
	return error;
}