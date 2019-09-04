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
typedef  int nspace_type_t ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
#define  NSPACE_HANDLER_NSPACE 129 
#define  NSPACE_HANDLER_SNAPSHOT 128 
 int O_EVTONLY ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static inline int nspace_open_flags_for_type(nspace_type_t nspace_type)
{
	switch(nspace_type) {
		case NSPACE_HANDLER_NSPACE:
			return FREAD | FWRITE | O_EVTONLY;
		case NSPACE_HANDLER_SNAPSHOT:
			return FREAD | O_EVTONLY;
		default:
			printf("nspace_open_flags_for_type: invalid type %u\n", (int)nspace_type);
			return 0;
	}
}