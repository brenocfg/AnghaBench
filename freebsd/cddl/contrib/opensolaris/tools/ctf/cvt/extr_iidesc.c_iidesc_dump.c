#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ii_type; char* ii_name; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,char*) ; 

int
iidesc_dump(iidesc_t *ii)
{
	printf("type: %d  name %s\n", ii->ii_type,
	    (ii->ii_name ? ii->ii_name : "(anon)"));

	return (0);
}