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
typedef  scalar_t__ u64 ;
struct getdents_callback {scalar_t__ ino; char* name; int found; int /*<<< orphan*/  sequence; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int filldir_one(void * __buf, const char * name, int len,
			loff_t pos, u64 ino, unsigned int d_type)
{
	struct getdents_callback *buf = __buf;
	int result = 0;

	buf->sequence++;
	if (buf->ino == ino) {
		memcpy(buf->name, name, len);
		buf->name[len] = '\0';
		buf->found = 1;
		result = -1;
	}
	return result;
}