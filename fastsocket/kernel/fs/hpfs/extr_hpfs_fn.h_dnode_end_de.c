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
typedef  void hpfs_dirent ;
struct dnode {int first_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHKCOND (int,char*) ; 

__attribute__((used)) static inline struct hpfs_dirent *dnode_end_de (struct dnode *dnode)
{
  CHKCOND(dnode->first_free>=0x14 && dnode->first_free<=0xa00,("HPFS: dnode_end_de: dnode->first_free = %d\n",(int)dnode->first_free));
  return (void *) dnode + dnode->first_free;
}