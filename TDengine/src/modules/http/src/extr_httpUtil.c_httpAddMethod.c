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
struct TYPE_3__ {int methodScannerLen; int /*<<< orphan*/ ** methodScanner; } ;
typedef  TYPE_1__ HttpServer ;
typedef  int /*<<< orphan*/  HttpDecodeMethod ;

/* Variables and functions */
 int HTTP_METHOD_SCANNER_SIZE ; 
 scalar_t__ httpCompareMethod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void httpAddMethod(HttpServer *pServer, HttpDecodeMethod *pMethod) {
  int pos = 0;
  for (pos = 0; pos < pServer->methodScannerLen; ++pos) {
    if (httpCompareMethod(pServer->methodScanner[pos], pMethod)) {
      break;
    }
  }

  if (pos == pServer->methodScannerLen && pServer->methodScannerLen < HTTP_METHOD_SCANNER_SIZE) {
    pServer->methodScanner[pos] = pMethod;
    pServer->methodScannerLen++;
  }
}