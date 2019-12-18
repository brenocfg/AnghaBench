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
typedef  int /*<<< orphan*/  SVnodeHeadInfo ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TSDB_FILE_HEADER_LEN ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twrite (int,int /*<<< orphan*/ *,int) ; 

void vnodeUpdateHeadFileHeader(int fd, SVnodeHeadInfo* pHeadInfo) {
  lseek(fd, TSDB_FILE_HEADER_LEN / 4, SEEK_SET);
  twrite(fd, pHeadInfo, sizeof(SVnodeHeadInfo));
}