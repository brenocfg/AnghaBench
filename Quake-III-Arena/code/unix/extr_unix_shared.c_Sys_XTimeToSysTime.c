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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int) ; 
 int Sys_Milliseconds () ; 
 TYPE_1__* in_subframe ; 
 int sys_timeBase ; 

int Sys_XTimeToSysTime (unsigned long xtime)
{
	int ret, time, test;
	
	if (!in_subframe->value)
	{
		// if you don't want to do any event times corrections
		return Sys_Milliseconds();
	}

	// test the wrap issue
#if 0	
	// reference values for test: sys_timeBase 0x3dc7b5e9 xtime 0x541ea451 (read these from a test run)
	// xtime will wrap in 0xabe15bae ms >~ 0x2c0056 s (33 days from Nov 5 2002 -> 8 Dec)
	//   NOTE: date -d '1970-01-01 UTC 1039384002 seconds' +%c
	// use sys_timeBase 0x3dc7b5e9+0x2c0056 = 0x3df3b63f
	// after around 5s, xtime would have wrapped around
	// we get 7132, the formula handles the wrap safely
	unsigned long xtime_aux,base_aux;
	int test;
//	Com_Printf("sys_timeBase: %p\n", sys_timeBase);
//	Com_Printf("xtime: %p\n", xtime);
	xtime_aux = 500; // 500 ms after wrap
	base_aux = 0x3df3b63f; // the base a few seconds before wrap
	test = xtime_aux - (unsigned long)(base_aux*1000);
	Com_Printf("xtime wrap test: %d\n", test);
#endif

  // some X servers (like suse 8.1's) report weird event times
  // if the game is loading, resolving DNS, etc. we are also getting old events
  // so we only deal with subframe corrections that look 'normal'
  ret = xtime - (unsigned long)(sys_timeBase*1000);
  time = Sys_Milliseconds();
  test = time - ret;
  //printf("delta: %d\n", test);
  if (test < 0 || test > 30) // in normal conditions I've never seen this go above
  {
    return time;
  }

	return ret;
}