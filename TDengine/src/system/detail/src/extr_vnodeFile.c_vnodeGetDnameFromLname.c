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

/* Variables and functions */
 int /*<<< orphan*/  TSDB_FILENAME_LEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readlink (char*,char*,int /*<<< orphan*/ ) ; 

void vnodeGetDnameFromLname(char *lhead, char *ldata, char *llast, char *dhead, char *ddata, char *dlast) {
  if (lhead != NULL) {
    assert(dhead != NULL);
    readlink(lhead, dhead, TSDB_FILENAME_LEN);
  }

  if (ldata != NULL) {
    assert(ddata != NULL);
    readlink(ldata, ddata, TSDB_FILENAME_LEN);
  }

  if (llast != NULL) {
    assert(dlast != NULL);
    readlink(llast, dlast, TSDB_FILENAME_LEN);
  }
}