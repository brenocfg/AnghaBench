#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * jsonBuf; } ;
typedef  int /*<<< orphan*/  JsonBuf ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

JsonBuf *httpMallocJsonBuf(HttpContext *pContext) {
  if (pContext->jsonBuf == NULL) {
    pContext->jsonBuf = (JsonBuf *)malloc(sizeof(JsonBuf));
  }

  return pContext->jsonBuf;
}