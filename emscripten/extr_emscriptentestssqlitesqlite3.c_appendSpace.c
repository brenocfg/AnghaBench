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
typedef  int /*<<< orphan*/  zSpaces ;
typedef  int /*<<< orphan*/  StrAccum ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3StrAccumAppend (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void appendSpace(StrAccum *pAccum, int N){
  static const char zSpaces[] = "                             ";
  while( N>=(int)sizeof(zSpaces)-1 ){
    sqlite3StrAccumAppend(pAccum, zSpaces, sizeof(zSpaces)-1);
    N -= sizeof(zSpaces)-1;
  }
  if( N>0 ){
    sqlite3StrAccumAppend(pAccum, zSpaces, N);
  }
}