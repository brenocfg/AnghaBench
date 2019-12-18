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
struct gdbstub_threadinfo {char* display; char* name; char* more_display; } ;
typedef  int s32 ;

/* Variables and functions */
 void** hexchars ; 
 char* int2fhstr (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* thread2fhstr (char*,int) ; 

void packqq(char *out,s32 mask,s32 thread,struct gdbstub_threadinfo *info)
{
	s32 len;

	*out++ = 'q';
	*out++ = 'Q';
	out = int2fhstr(out,mask);
	out = thread2fhstr(out,thread);

	if(mask&0x01) {
		memcpy(out,"00000001",8);
		out += 8;
		*out++ = '1';
		*out++ = '0';
		out = thread2fhstr(out,thread);
	}
	if(mask&0x02) {
		memcpy(out,"00000002",8);
		out += 8;
		*out++ = '0';
		*out++ = '1';
		*out++ = '1';
	}
	if(mask&0x04) {
		memcpy(out,"00000004",8);
		out += 8;

		info->display[sizeof(info->display)-1] = 0;			//for god sake
		len = strlen(info->display);

		*out++ = hexchars[(len>>4)&0x0f];
		*out++ = hexchars[len&0x0f];

		memcpy(out,info->display,len);
		out += len;
	}
	if(mask&0x08) {
		memcpy(out,"00000008",8);
		out += 8;

		info->display[sizeof(info->name)-1] = 0;			//for god sake
		len = strlen(info->name);

		*out++ = hexchars[(len>>4)&0x0f];
		*out++ = hexchars[len&0x0f];

		memcpy(out,info->name,len);
		out += len;
	}
	if(mask&0x10) {
		memcpy(out,"00000010",8);
		out += 8;

		info->display[sizeof(info->more_display)-1] = 0;			//for god sake
		len = strlen(info->more_display);

		*out++ = hexchars[(len>>4)&0x0f];
		*out++ = hexchars[len&0x0f];

		memcpy(out,info->more_display,len);
		out += len;
	}
	*out = 0;
}