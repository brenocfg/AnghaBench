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
typedef  int /*<<< orphan*/  HttpServer ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TELEGRAF_CFG ; 
 char* configDir ; 
 int /*<<< orphan*/  httpAddMethod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  tgDecodeMethod ; 
 int /*<<< orphan*/  tgFreeSchemas () ; 
 scalar_t__ tgParseSchema (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tgReadSchema (char*) ; 

void tgInitHandle(HttpServer *pServer) {
  char fileName[256] = {0};
  sprintf(fileName, "%s/taos.telegraf.cfg", configDir);
  if (tgReadSchema(fileName) <= 0) {
    tgFreeSchemas();
    if (tgParseSchema(DEFAULT_TELEGRAF_CFG, "default") <= 0) {
      tgFreeSchemas();
    }
  }

  httpAddMethod(pServer, &tgDecodeMethod);
}