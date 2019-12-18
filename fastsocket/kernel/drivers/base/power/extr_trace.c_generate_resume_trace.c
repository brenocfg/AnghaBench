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

/* Variables and functions */
 int /*<<< orphan*/  FILEHASH ; 
 unsigned int USERHASH ; 
 int /*<<< orphan*/  dev_hash_value ; 
 unsigned int hash_string (unsigned short,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_magic_time (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

void generate_resume_trace(const void *tracedata, unsigned int user)
{
	unsigned short lineno = *(unsigned short *)tracedata;
	const char *file = *(const char **)(tracedata + 2);
	unsigned int user_hash_value, file_hash_value;

	user_hash_value = user % USERHASH;
	file_hash_value = hash_string(lineno, file, FILEHASH);
	set_magic_time(user_hash_value, file_hash_value, dev_hash_value);
}