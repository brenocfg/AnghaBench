#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct ps_prochandle {int dummy; } ;
struct TYPE_9__ {int ftps_pc; int ftps_size; scalar_t__ ftps_noffs; int* ftps_offs; int /*<<< orphan*/  ftps_type; } ;
typedef  TYPE_1__ fasttrap_probe_spec_t ;
struct TYPE_10__ {int /*<<< orphan*/  dt_ftfd; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_11__ {int st_size; int st_value; } ;
typedef  TYPE_3__ GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  DTFTP_RETURN ; 
 int DT_PROC_ERR ; 
 int /*<<< orphan*/  FASTTRAPIOC_MAKEPROBE ; 
 int Pread (struct ps_prochandle*,int*,int,int) ; 
 int UINTPTR_MAX ; 
 int /*<<< orphan*/  dt_dprintf (char*,...) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int* malloc (int) ; 
 int strerror (int /*<<< orphan*/ ) ; 

int
dt_pid_create_return_probe(struct ps_prochandle *P, dtrace_hdl_t *dtp,
    fasttrap_probe_spec_t *ftp, const GElf_Sym *symp, uint64_t *stret)
{

	uintptr_t temp;
	uint32_t *text;
	int i;
	int srdepth = 0;

	if ((text = malloc(symp->st_size + 4)) == NULL) {
		dt_dprintf("mr sparkle: malloc() failed\n");
		return (DT_PROC_ERR);
	}

	if (Pread(P, text, symp->st_size, symp->st_value) != symp->st_size) {
		dt_dprintf("mr sparkle: Pread() failed\n");
		free(text);
		return (DT_PROC_ERR);
	}

	/*
	 * Leave a dummy instruction in the last slot to simplify edge
	 * conditions.
	 */
	text[symp->st_size / 4] = 0;

	ftp->ftps_type = DTFTP_RETURN;
	ftp->ftps_pc = symp->st_value;
	ftp->ftps_size = symp->st_size;
	ftp->ftps_noffs = 0;

	for (i = 0; i < symp->st_size / 4; i++) {

		if ((text[i] & 0xfc000001) != 0x48000000 &&
		    text[i] != 0x4e800020)
			continue;

		/*
		 * Check for a jump within this function.  If it's outside this
		 * function then it's a tail-call, so a return point.
		 */
		if ((text[i] & 0xfc000000) == 0x48000000) {
			temp = (text[i] & 0x03fffffc);
			/* Bit 30 denotes an absolute address. */
			if (!(text[i] & 0x02)) {
				temp += symp->st_value + i * 4;
			}
			else {
				/* Sign extend the absolute address. */
				if (temp & 0x02000000) {
					temp |= (UINTPTR_MAX - 0x03ffffff);
				}
			}
			if (temp >= symp->st_value &&
			    temp <= (symp->st_value + symp->st_size))
				continue;
		}
		dt_dprintf("return at offset %x\n", i * 4);
		ftp->ftps_offs[ftp->ftps_noffs++] = i * 4;
	}

	free(text);
	if (ftp->ftps_noffs > 0) {
		if (ioctl(dtp->dt_ftfd, FASTTRAPIOC_MAKEPROBE, ftp) != 0) {
			dt_dprintf("fasttrap probe creation ioctl failed: %s\n",
			    strerror(errno));
			return (dt_set_errno(dtp, errno));
		}
	}


	return (ftp->ftps_noffs);
}