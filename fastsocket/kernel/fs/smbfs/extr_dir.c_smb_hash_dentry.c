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
struct qstr {int len; int /*<<< orphan*/  hash; int /*<<< orphan*/ * name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned long init_name_hash () ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
smb_hash_dentry(struct dentry *dir, struct qstr *this)
{
	unsigned long hash;
	int i;

	hash = init_name_hash();
	for (i=0; i < this->len ; i++)
		hash = partial_name_hash(tolower(this->name[i]), hash);
	this->hash = end_name_hash(hash);
  
	return 0;
}