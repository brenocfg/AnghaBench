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
struct timeval {float tv_sec; float tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

double opj_clock(void) {
#ifdef _WIN32
	/* _WIN32: use QueryPerformance (very accurate) */
    LARGE_INTEGER freq , t ;
    /* freq is the clock speed of the CPU */
    QueryPerformanceFrequency(&freq) ;
	/* cout << "freq = " << ((double) freq.QuadPart) << endl; */
    /* t is the high resolution performance counter (see MSDN) */
    QueryPerformanceCounter ( & t ) ;
    return ( t.QuadPart /(double) freq.QuadPart ) ;
#else
#if 0 /* EMSCRIPTEN: ifdef this out, and add code to use gettimeofday instead of getrusage */
	/* Unix or Linux: use resource usage */
    struct rusage t;
    double procTime;
    /* (1) Get the rusage data structure at this moment (man getrusage) */
    getrusage(0,&t);
    /* (2) What is the elapsed time ? - CPU time = User time + System time */
	/* (2a) Get the seconds */
    procTime = t.ru_utime.tv_sec + t.ru_stime.tv_sec;
    /* (2b) More precisely! Get the microseconds part ! */
    return ( procTime + (t.ru_utime.tv_usec + t.ru_stime.tv_usec) * 1e-6 ) ;
#else
    struct timeval tv;
    static double last = -1;
    double curr, ret;
    gettimeofday(&tv, NULL);
    curr = tv.tv_sec + tv.tv_usec/(1000.0f*1000.0f);
    if (last < 0) last = curr;
    ret = curr - last;
    last = curr;
    return ret;
#endif
#endif
}