#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  singleCmd; TYPE_1__* encodeMethod; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* stopJsonFp ) (TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* startJsonFp ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ HttpEncodeMethod ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpCloseContextByApp (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 

void httpProcessHeartBeatCmd(HttpContext *pContext) {
  HttpEncodeMethod *encode = pContext->encodeMethod;
  if (encode->startJsonFp) {
    (encode->startJsonFp)(pContext, &pContext->singleCmd, NULL);
  }
  if (encode->stopJsonFp) {
    (encode->stopJsonFp)(pContext, &pContext->singleCmd);
  }
  httpCloseContextByApp(pContext);
}