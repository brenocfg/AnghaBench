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
typedef  scalar_t__ uint_t ;
typedef  char* time_t ;
typedef  int /*<<< orphan*/  dstr ;

/* Variables and functions */
 scalar_t__ DDATE ; 
 scalar_t__ UDATE ; 
 int /*<<< orphan*/  localtime (char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* time (int /*<<< orphan*/ *) ; 

void
print_timestamp(uint_t timestamp_fmt)
{
	time_t t = time(NULL);

	if (timestamp_fmt == UDATE) {
		(void) printf("%ld\n", t);
	} else if (timestamp_fmt == DDATE) {
		char dstr[64];
		int len;

		len = strftime(dstr, sizeof (dstr), "%+", localtime(&t));
		if (len > 0)
			(void) printf("%s\n", dstr);
	}
}