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
struct hpfs_dirent {int length; int /*<<< orphan*/  down; } ;
typedef  int /*<<< orphan*/  dnode_secno ;

/* Variables and functions */
 int /*<<< orphan*/  CHKCOND (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline dnode_secno de_down_pointer (struct hpfs_dirent *de)
{
  CHKCOND(de->down,("HPFS: de_down_pointer: !de->down\n"));
  return *(dnode_secno *) ((void *) de + de->length - 4);
}