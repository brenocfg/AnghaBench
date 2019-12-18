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
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  TYPE_1__* backing_store_ptr ;
struct TYPE_3__ {int /*<<< orphan*/  temp_name; int /*<<< orphan*/  close_backing_store; int /*<<< orphan*/  write_backing_store; int /*<<< orphan*/  read_backing_store; int /*<<< orphan*/ * temp_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERREXITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERR_TFILE_CREATE ; 
 int /*<<< orphan*/  JTRC_TFILE_OPEN ; 
 int /*<<< orphan*/  RW_BINARY ; 
 int /*<<< orphan*/  TRACEMSS (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_backing_store ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_backing_store ; 
 int /*<<< orphan*/  select_file_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_backing_store ; 

void
jpeg_open_backing_store (j_common_ptr cinfo, backing_store_ptr info,
			 long total_bytes_needed)
{
  select_file_name(info->temp_name);
  if ((info->temp_file = fopen(info->temp_name, RW_BINARY)) == NULL)
    ERREXITS(cinfo, JERR_TFILE_CREATE, info->temp_name);
  info->read_backing_store = read_backing_store;
  info->write_backing_store = write_backing_store;
  info->close_backing_store = close_backing_store;
  TRACEMSS(cinfo, 1, JTRC_TFILE_OPEN, info->temp_name);
}