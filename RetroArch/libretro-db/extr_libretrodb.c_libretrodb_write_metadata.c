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
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ libretrodb_metadata_t ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  STRLEN_CONST (char*) ; 
 int /*<<< orphan*/  rmsgpack_write_map_header (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rmsgpack_write_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int rmsgpack_write_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libretrodb_write_metadata(RFILE *fd, libretrodb_metadata_t *md)
{
   rmsgpack_write_map_header(fd, 1);
   rmsgpack_write_string(fd, "count", STRLEN_CONST("count"));
   return rmsgpack_write_uint(fd, md->count);
}