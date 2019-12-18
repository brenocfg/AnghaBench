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
struct pevent {int dummy; } ;

/* Variables and functions */
 int read4 (struct pevent*) ; 
 unsigned long long read8 (struct pevent*) ; 
 int /*<<< orphan*/  read_event_file (struct pevent*,char*,unsigned long long) ; 
 char* read_string () ; 

__attribute__((used)) static void read_event_files(struct pevent *pevent)
{
	unsigned long long size;
	char *sys;
	int systems;
	int count;
	int i,x;

	systems = read4(pevent);

	for (i = 0; i < systems; i++) {
		sys = read_string();

		count = read4(pevent);
		for (x=0; x < count; x++) {
			size = read8(pevent);
			read_event_file(pevent, sys, size);
		}
	}
}