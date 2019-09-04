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
 int /*<<< orphan*/  disable_branch_tracing () ; 
 unsigned int* pc_buffer ; 
 unsigned int* pc_buflast ; 
 unsigned int* pc_bufptr ; 
 unsigned int* pc_trace_buf ; 
 int pc_trace_cnt ; 
 unsigned int pcsample_beg ; 
 scalar_t__ pcsample_enable ; 
 unsigned int pcsample_end ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
add_pcbuffer(void)
{
	int      i;
	unsigned int  pc; 

	if (!pcsample_enable)
	  return;

	for (i=0; i < pc_trace_cnt; i++)
	  {
	    pc = pc_trace_buf[i];
	    
	    if ((pcsample_beg <= pc) && (pc < pcsample_end))
	      {
		if (pc_bufptr > pc_buffer)
		  {
		    if ( (*(pc_bufptr-1)) == pc )
		      continue;   /* Ignore, probably spinning */
		  }

		/* Then the sample is in our range */
		*pc_bufptr = pc;
		pc_bufptr++;
	      }
	  }

	/* We never wrap the buffer */
	if ((pc_bufptr + pc_trace_cnt) >= pc_buflast)
	  {
	    pcsample_enable = 0;
	    (void)disable_branch_tracing();
	    wakeup(&pcsample_enable);
	  }
	return;
}