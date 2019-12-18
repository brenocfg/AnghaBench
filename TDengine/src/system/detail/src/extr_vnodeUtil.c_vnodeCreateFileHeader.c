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
typedef  int /*<<< orphan*/  temp ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TSDB_FILE_HEADER_LEN ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* version ; 
 int /*<<< orphan*/  vnodeFileVersion ; 

void vnodeCreateFileHeader(FILE* fp) {
  char temp[TSDB_FILE_HEADER_LEN / 4];
  int  lineLen;

  lineLen = sizeof(temp);

  // write the first line
  memset(temp, 0, lineLen);
  *(int16_t*)temp = vnodeFileVersion;
  sprintf(temp + sizeof(int16_t), "tsdb version: %s\n", version);
  /* *((int16_t *)(temp + TSDB_FILE_HEADER_LEN/8)) = vnodeFileVersion; */
  fseek(fp, 0, SEEK_SET);
  fwrite(temp, lineLen, 1, fp);

  // second line
  memset(temp, 0, lineLen);
  fwrite(temp, lineLen, 1, fp);

  // the third line is the dynamic info
  memset(temp, 0, lineLen);
  fwrite(temp, lineLen, 1, fp);
  fwrite(temp, lineLen, 1, fp);
}