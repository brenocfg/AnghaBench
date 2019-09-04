#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cio; TYPE_2__* cp; } ;
typedef  TYPE_1__ opj_j2k_t ;
struct TYPE_5__ {int ppm; int ppm_previous; int ppm_store; unsigned char* ppm_data; unsigned char* ppm_data_first; int ppm_len; } ;
typedef  TYPE_2__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ opj_malloc (int) ; 
 scalar_t__ opj_realloc (unsigned char*,int) ; 

__attribute__((used)) static void j2k_read_ppm(opj_j2k_t *j2k) {
	int len, Z_ppm, i, j;
	int N_ppm;

	opj_cp_t *cp = j2k->cp;
	opj_cio_t *cio = j2k->cio;
	
	len = cio_read(cio, 2);
	cp->ppm = 1;
	
	Z_ppm = cio_read(cio, 1);	/* Z_ppm */
	len -= 3;
	while (len > 0) {
		if (cp->ppm_previous == 0) {
			N_ppm = cio_read(cio, 4);	/* N_ppm */
			len -= 4;
		} else {
			N_ppm = cp->ppm_previous;
		}
		j = cp->ppm_store;
		if (Z_ppm == 0) {	/* First PPM marker */
			cp->ppm_data = (unsigned char *) opj_malloc(N_ppm * sizeof(unsigned char));
			cp->ppm_data_first = cp->ppm_data;
			cp->ppm_len = N_ppm;
		} else {			/* NON-first PPM marker */
			cp->ppm_data = (unsigned char *) opj_realloc(cp->ppm_data, (N_ppm +	cp->ppm_store) * sizeof(unsigned char));

#ifdef USE_JPWL
			/* this memory allocation check could be done even in non-JPWL cases */
			if (cp->correct) {
				if (!cp->ppm_data) {
					opj_event_msg(j2k->cinfo, EVT_ERROR,
						"JPWL: failed memory allocation during PPM marker parsing (pos. %x)\n",
						cio_tell(cio));
					if (!JPWL_ASSUME || JPWL_ASSUME) {
						opj_free(cp->ppm_data);
						opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
						return;
					}
				}
			}
#endif

			cp->ppm_data_first = cp->ppm_data;
			cp->ppm_len = N_ppm + cp->ppm_store;
		}
		for (i = N_ppm; i > 0; i--) {	/* Read packet header */
			cp->ppm_data[j] = cio_read(cio, 1);
			j++;
			len--;
			if (len == 0)
				break;			/* Case of non-finished packet header in present marker but finished in next one */
		}
		cp->ppm_previous = i - 1;
		cp->ppm_store = j;
	}
}