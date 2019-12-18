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
typedef  int ttreq_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TTRACE_REQ (int) ; 
#define  TT_LWP_CONTINUE 135 
#define  TT_LWP_GET_EVENT_MASK 134 
#define  TT_LWP_GET_STATE 133 
#define  TT_LWP_RUREGS 132 
#define  TT_LWP_SET_EVENT_MASK 131 
#define  TT_LWP_SINGLE 130 
#define  TT_LWP_STOP 129 
#define  TT_LWP_WUREGS 128 
 int TT_PROC_CONTINUE ; 
 int TT_PROC_GET_EVENT_MASK ; 
 int TT_PROC_SET_EVENT_MASK ; 
 int TT_PROC_STOP ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static ttreq_t
make_process_version (ttreq_t request)
{
  if (!IS_TTRACE_REQ (request))
    {
      error ("Internal error, bad ttrace request made\n");
      return -1;
    }

  switch (request)
    {
    case TT_LWP_STOP:
      return TT_PROC_STOP;

    case TT_LWP_CONTINUE:
      return TT_PROC_CONTINUE;

    case TT_LWP_GET_EVENT_MASK:
      return TT_PROC_GET_EVENT_MASK;

    case TT_LWP_SET_EVENT_MASK:
      return TT_PROC_SET_EVENT_MASK;

    case TT_LWP_SINGLE:
    case TT_LWP_RUREGS:
    case TT_LWP_WUREGS:
    case TT_LWP_GET_STATE:
      return -1;		/* No equivalent */

    default:
      return request;
    }
}