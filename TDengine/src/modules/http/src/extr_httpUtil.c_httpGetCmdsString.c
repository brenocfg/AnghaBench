#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* multiCmds; } ;
struct TYPE_4__ {int bufferSize; char* buffer; } ;
typedef  TYPE_1__ HttpSqlCmds ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */

char *httpGetCmdsString(HttpContext *pContext, int pos) {
  HttpSqlCmds *multiCmds = pContext->multiCmds;
  if (pos < 0 || pos >= multiCmds->bufferSize) {
    return "";
  }

  return multiCmds->buffer + pos;
}