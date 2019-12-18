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
typedef  int HttpContextState ;

/* Variables and functions */
#define  HTTP_CONTEXT_STATE_CLOSED 131 
#define  HTTP_CONTEXT_STATE_DROPPING 130 
#define  HTTP_CONTEXT_STATE_HANDLING 129 
#define  HTTP_CONTEXT_STATE_READY 128 

const char* httpContextStateStr(HttpContextState state) {
  switch (state) {
    case HTTP_CONTEXT_STATE_READY:
      return "ready";
    case HTTP_CONTEXT_STATE_HANDLING:
      return "handling";
    case HTTP_CONTEXT_STATE_DROPPING:
      return "dropping";
    case HTTP_CONTEXT_STATE_CLOSED:
      return "closed";
    default:
      return "unknown";
  }
}