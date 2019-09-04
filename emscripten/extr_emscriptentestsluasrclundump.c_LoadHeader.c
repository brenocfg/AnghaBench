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
typedef  int /*<<< orphan*/  lu_byte ;
typedef  int /*<<< orphan*/  LoadState ;

/* Variables and functions */
 int LUAC_HEADERSIZE ; 
 int /*<<< orphan*/  LoadBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  N0 ; 
 int /*<<< orphan*/  N1 ; 
 int /*<<< orphan*/  N2 ; 
 int /*<<< orphan*/  N3 ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaU_header (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void LoadHeader(LoadState* S)
{
 lu_byte h[LUAC_HEADERSIZE];
 lu_byte s[LUAC_HEADERSIZE];
 luaU_header(h);
 memcpy(s,h,sizeof(char));			/* first char already read */
 LoadBlock(S,s+sizeof(char),LUAC_HEADERSIZE-sizeof(char));
 if (memcmp(h,s,N0)==0) return;
 if (memcmp(h,s,N1)!=0) error(S,"not a");
 if (memcmp(h,s,N2)!=0) error(S,"version mismatch in");
 if (memcmp(h,s,N3)!=0) error(S,"incompatible"); else error(S,"corrupted");
}