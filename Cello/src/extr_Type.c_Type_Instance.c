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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 int /*<<< orphan*/  Alloc ; 
 int /*<<< orphan*/  Assign ; 
 int /*<<< orphan*/  C_Float ; 
 int /*<<< orphan*/  C_Int ; 
 int /*<<< orphan*/  C_Str ; 
 int /*<<< orphan*/  Cast ; 
 int /*<<< orphan*/  Cmp ; 
 int /*<<< orphan*/  Concat ; 
 int /*<<< orphan*/  Current ; 
 int /*<<< orphan*/  Get ; 
 int /*<<< orphan*/  Hash ; 
 int /*<<< orphan*/  Iter ; 
 int /*<<< orphan*/  Len ; 
 int /*<<< orphan*/  Mark ; 
 int /*<<< orphan*/  New ; 
 int /*<<< orphan*/  Pointer ; 
 int /*<<< orphan*/  Push ; 
 int /*<<< orphan*/  Size ; 
 int /*<<< orphan*/  Type_Cache_Entry (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Type_Scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static var Type_Instance(var self, var cls) {

#if CELLO_CACHE == 1
  Type_Cache_Entry( 0, Size);    Type_Cache_Entry( 1, Alloc);
  Type_Cache_Entry( 2, New);     Type_Cache_Entry( 3, Assign);
  Type_Cache_Entry( 4, Cmp);     Type_Cache_Entry( 5, Mark);
  Type_Cache_Entry( 6, Hash);    Type_Cache_Entry( 7, Len);
  Type_Cache_Entry( 8, Iter);    Type_Cache_Entry( 9, Push);
  Type_Cache_Entry(10, Concat);  Type_Cache_Entry(11, Get);
  Type_Cache_Entry(12, C_Str);   Type_Cache_Entry(13, C_Int);
  Type_Cache_Entry(14, C_Float); Type_Cache_Entry(15, Current);
  Type_Cache_Entry(16, Cast);    Type_Cache_Entry(17, Pointer);
#endif
  
  return Type_Scan(self, cls);
}