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
struct yytbl_hdr {void* th_name; void* th_version; scalar_t__ th_flags; scalar_t__ th_ssize; scalar_t__ th_hsize; int /*<<< orphan*/  th_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  YYTBL_MAGIC ; 
 void* copy_string (char const*) ; 
 int /*<<< orphan*/  memset (struct yytbl_hdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ yypad64 (scalar_t__) ; 

int yytbl_hdr_init (struct yytbl_hdr *th, const char *version_str,
		    const char *name)
{
	memset (th, 0, sizeof (struct yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = 14 + strlen (version_str) + 1 + strlen (name) + 1;
	th->th_hsize += yypad64 (th->th_hsize);
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_version = copy_string (version_str);
	th->th_name = copy_string (name);
	return 0;
}