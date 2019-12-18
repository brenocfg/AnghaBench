#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pe_fd; int pe_cmd; int /*<<< orphan*/  pe_scn; int /*<<< orphan*/  pe_obj; } ;
typedef  int /*<<< orphan*/  PE_Object ;
typedef  int PE_Cmd ;
typedef  TYPE_1__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  PE_C_RDWR 130 
#define  PE_C_READ 129 
#define  PE_C_WRITE 128 
 int /*<<< orphan*/  PE_O_COFF ; 
 int /*<<< orphan*/  PE_O_PE32 ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libpe_open_object (TYPE_1__*) ; 
 int /*<<< orphan*/  pe_finish (TYPE_1__*) ; 

PE *
pe_init(int fd, PE_Cmd c, PE_Object o)
{
	PE *pe;

	if ((pe = calloc(1, sizeof(*pe))) == NULL) {
		errno = ENOMEM;
		return (NULL);
	}
	pe->pe_fd = fd;
	pe->pe_cmd = c;
	pe->pe_obj = o;
	STAILQ_INIT(&pe->pe_scn);

	switch (c) {
	case PE_C_READ:
	case PE_C_RDWR:
		if (libpe_open_object(pe) < 0)
			goto init_fail;
		break;

	case PE_C_WRITE:
		if (o < PE_O_PE32 || o > PE_O_COFF) {
			errno = EINVAL;
			goto init_fail;
		}
		break;

	default:
		errno = EINVAL;
		goto init_fail;
	}

	return (pe);

init_fail:
	pe_finish(pe);
	return (NULL);
}