#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* path; } ;
struct TYPE_7__ {TYPE_2__ parser; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ HttpParser ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int HTTP_MAX_URL ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bool httpUrlMatch(HttpContext* pContext, int pos, char* cmp) {
  HttpParser* pParser = &pContext->parser;

  if (pos < 0 || pos >= HTTP_MAX_URL) {
    return false;
  }

  if (pParser->path[pos].len <= 0) {
    return false;
  }

  if (strcmp(pParser->path[pos].pos, cmp) != 0) {
    return false;
  }

  return true;
}