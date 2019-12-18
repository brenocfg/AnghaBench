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
#define  TT_LWP_CONTINUE 153 
#define  TT_LWP_GET_EVENT_MASK 152 
#define  TT_LWP_GET_STATE 151 
#define  TT_LWP_RUREGS 150 
#define  TT_LWP_SET_EVENT_MASK 149 
#define  TT_LWP_SINGLE 148 
#define  TT_LWP_STOP 147 
#define  TT_LWP_WUREGS 146 
#define  TT_PROC_ATTACH 145 
#define  TT_PROC_CONTINUE 144 
#define  TT_PROC_DETACH 143 
#define  TT_PROC_EXIT 142 
#define  TT_PROC_GET_EVENT_MASK 141 
#define  TT_PROC_GET_FIRST_LWP_STATE 140 
#define  TT_PROC_GET_MPROTECT 139 
#define  TT_PROC_GET_NEXT_LWP_STATE 138 
#define  TT_PROC_GET_PATHNAME 137 
#define  TT_PROC_RDDATA 136 
#define  TT_PROC_RDTEXT 135 
#define  TT_PROC_SETTRC 134 
#define  TT_PROC_SET_EVENT_MASK 133 
#define  TT_PROC_SET_MPROTECT 132 
#define  TT_PROC_SET_SCBM 131 
#define  TT_PROC_STOP 130 
#define  TT_PROC_WRDATA 129 
#define  TT_PROC_WRTEXT 128 

char *
get_printable_name_of_ttrace_request (ttreq_t request)
{
  if (!IS_TTRACE_REQ (request))
    return "?bad req?";

  /* This enumeration is "gappy", so don't use a table. */
  switch (request)
    {
    case TT_PROC_SETTRC:
      return "TT_PROC_SETTRC";
    case TT_PROC_ATTACH:
      return "TT_PROC_ATTACH";
    case TT_PROC_DETACH:
      return "TT_PROC_DETACH";
    case TT_PROC_RDTEXT:
      return "TT_PROC_RDTEXT";
    case TT_PROC_WRTEXT:
      return "TT_PROC_WRTEXT";
    case TT_PROC_RDDATA:
      return "TT_PROC_RDDATA";
    case TT_PROC_WRDATA:
      return "TT_PROC_WRDATA";
    case TT_PROC_STOP:
      return "TT_PROC_STOP";
    case TT_PROC_CONTINUE:
      return "TT_PROC_CONTINUE";
    case TT_PROC_GET_PATHNAME:
      return "TT_PROC_GET_PATHNAME";
    case TT_PROC_GET_EVENT_MASK:
      return "TT_PROC_GET_EVENT_MASK";
    case TT_PROC_SET_EVENT_MASK:
      return "TT_PROC_SET_EVENT_MASK";
    case TT_PROC_GET_FIRST_LWP_STATE:
      return "TT_PROC_GET_FIRST_LWP_STATE";
    case TT_PROC_GET_NEXT_LWP_STATE:
      return "TT_PROC_GET_NEXT_LWP_STATE";
    case TT_PROC_EXIT:
      return "TT_PROC_EXIT";
    case TT_PROC_GET_MPROTECT:
      return "TT_PROC_GET_MPROTECT";
    case TT_PROC_SET_MPROTECT:
      return "TT_PROC_SET_MPROTECT";
    case TT_PROC_SET_SCBM:
      return "TT_PROC_SET_SCBM";
    case TT_LWP_STOP:
      return "TT_LWP_STOP";
    case TT_LWP_CONTINUE:
      return "TT_LWP_CONTINUE";
    case TT_LWP_SINGLE:
      return "TT_LWP_SINGLE";
    case TT_LWP_RUREGS:
      return "TT_LWP_RUREGS";
    case TT_LWP_WUREGS:
      return "TT_LWP_WUREGS";
    case TT_LWP_GET_EVENT_MASK:
      return "TT_LWP_GET_EVENT_MASK";
    case TT_LWP_SET_EVENT_MASK:
      return "TT_LWP_SET_EVENT_MASK";
    case TT_LWP_GET_STATE:
      return "TT_LWP_GET_STATE";
    default:
      return "?new req?";
    }
}