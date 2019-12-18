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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpError (char*,char const*) ; 
 int /*<<< orphan*/  httpPrint (char*,char const*,...) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int tgParseSchema (char*,char const*) ; 

int tgReadSchema(const char *fileName) {
  FILE *fp = fopen(fileName, "r");
  if (fp == NULL) {
    return -1;
  }

  httpPrint("open telegraf schema file:%s success", fileName);
  fseek(fp, 0, SEEK_END);
  size_t contentSize = (size_t)ftell(fp);
  rewind(fp);
  char *content = (char *)calloc(contentSize * sizeof(char) + 1, 1);
  size_t result = fread(content, 1, contentSize, fp);
  if (result != contentSize) {
    httpError("failed to read telegraf schema file:%s", fileName);
    return -1;
  }

  int schemaNum = tgParseSchema(content, fileName);

  free(content);
  fclose(fp);
  httpPrint("parse telegraf schema file:%s, schema size:%d", fileName, schemaNum);

  return schemaNum;
}