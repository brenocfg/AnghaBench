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
struct reiserfs_key {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_GENERATION_NUMBER (scalar_t__) ; 
 scalar_t__ GET_HASH_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_DIRENTRY ; 
 scalar_t__ le_key_k_offset (int,struct reiserfs_key*) ; 
 scalar_t__ le_key_k_type (int,struct reiserfs_key*) ; 
 int le_key_version (struct reiserfs_key*) ; 
 char* off_buf ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long,...) ; 

__attribute__((used)) static char *le_offset(struct reiserfs_key *key)
{
	int version;

	version = le_key_version(key);
	if (le_key_k_type(version, key) == TYPE_DIRENTRY)
		sprintf(off_buf, "%Lu(%Lu)",
			(unsigned long long)
			GET_HASH_VALUE(le_key_k_offset(version, key)),
			(unsigned long long)
			GET_GENERATION_NUMBER(le_key_k_offset(version, key)));
	else
		sprintf(off_buf, "0x%Lx",
			(unsigned long long)le_key_k_offset(version, key));
	return off_buf;
}