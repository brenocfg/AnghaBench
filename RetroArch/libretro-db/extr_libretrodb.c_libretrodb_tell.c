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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ libretrodb_t ;

/* Variables and functions */
 int /*<<< orphan*/  filestream_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t libretrodb_tell(libretrodb_t *db)
{
   return filestream_tell(db->fd);
}