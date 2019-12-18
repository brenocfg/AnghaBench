#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct savekmsg {int dummy; } ;
struct console {int dummy; } ;
struct TYPE_2__ {int size; int data; } ;

/* Variables and functions */
 int SAVEKMSG_MAXMEM ; 
 int /*<<< orphan*/  memcpy (int,char const*,unsigned int) ; 
 TYPE_1__* savekmsg ; 

__attribute__((used)) static void amiga_mem_console_write(struct console *co, const char *s,
				    unsigned int count)
{
	if (savekmsg->size + count <= SAVEKMSG_MAXMEM-sizeof(struct savekmsg)) {
		memcpy(savekmsg->data + savekmsg->size, s, count);
		savekmsg->size += count;
	}
}