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
typedef  void* uint16_t ;
struct changer_element_status_request {int cesr_element_count; struct changer_element_status* cesr_element_status; int /*<<< orphan*/  cesr_flags; void* cesr_element_base; void* cesr_element_type; } ;
struct changer_element_status {int dummy; } ;
typedef  int /*<<< orphan*/  cesr ;

/* Variables and functions */
 int /*<<< orphan*/  CESR_VOLTAGS ; 
 int /*<<< orphan*/  CHIOGSTATUS ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  changer_fd ; 
 int /*<<< orphan*/  changer_name ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (struct changer_element_status*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct changer_element_status_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct changer_element_status *
get_element_status(unsigned int type, unsigned int element, int use_voltags)
{
	struct changer_element_status_request cesr;
	struct changer_element_status *ces;
	
	ces = (struct changer_element_status *)
	    calloc((size_t)1, sizeof(struct changer_element_status));

	if (NULL == ces)
		errx(1, "can't allocate status storage");

	(void)memset(&cesr, 0, sizeof(cesr));

	cesr.cesr_element_type = (uint16_t)type;
	cesr.cesr_element_base = (uint16_t)element;
	cesr.cesr_element_count = 1;		/* Only this one element */
	if (use_voltags)
		cesr.cesr_flags |= CESR_VOLTAGS; /* Grab voltags as well */
	cesr.cesr_element_status = ces;

	if (ioctl(changer_fd, CHIOGSTATUS, (char *)&cesr) == -1) {
		free(ces);
		err(1, "%s: CHIOGSTATUS", changer_name);
		/* NOTREACHED */
	}

	return ces;
}