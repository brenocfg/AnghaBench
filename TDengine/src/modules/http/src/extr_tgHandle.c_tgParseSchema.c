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
typedef  int /*<<< orphan*/  cJSON ;

/* Variables and functions */
 int /*<<< orphan*/  cJSON_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cJSON_GetArrayItem (int /*<<< orphan*/ *,int) ; 
 int cJSON_GetArraySize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cJSON_GetObjectItem (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * cJSON_Parse (char*) ; 
 int /*<<< orphan*/  httpError (char*,char*,...) ; 
 int /*<<< orphan*/  tgInitSchemas (int) ; 
 int /*<<< orphan*/  tgParseSchemaMetric (int /*<<< orphan*/ *) ; 

int tgParseSchema(char *content, char*fileName) {
  cJSON *root = cJSON_Parse(content);
  if (root == NULL) {
    httpError("failed to parse telegraf schema file:%s, invalid json format, content:%s", fileName, content);
    return -1;
  }
  int size = 0;
  cJSON *metrics = cJSON_GetObjectItem(root, "metrics");
  if (metrics != NULL) {
    size = cJSON_GetArraySize(metrics);
    if (size <= 0) {
      httpError("failed to parse telegraf schema file:%s, metrics size is 0", fileName);
      cJSON_Delete(root);
      return -1;
    }

    tgInitSchemas(size);
    for (int i = 0; i < size; i++) {
      cJSON *metric = cJSON_GetArrayItem(metrics, i);
      if (metric != NULL) {
        tgParseSchemaMetric(metric);
      }
    }
  } else {
    size = 1;
    tgInitSchemas(size);
    tgParseSchemaMetric(root);
  }

  cJSON_Delete(root);
  return size;
}