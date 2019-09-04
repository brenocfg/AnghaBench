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
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_3__ {int flags; void const* z; scalar_t__ n; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int MEM_Blob ; 
 int MEM_Str ; 
 int /*<<< orphan*/  sqlite3VdbeMemExpandBlob (TYPE_1__*) ; 
 void const* sqlite3_value_text (int /*<<< orphan*/ *) ; 

const void *sqlite3_value_blob(sqlite3_value *pVal){
  Mem *p = (Mem*)pVal;
  if( p->flags & (MEM_Blob|MEM_Str) ){
    sqlite3VdbeMemExpandBlob(p);
    p->flags &= ~MEM_Str;
    p->flags |= MEM_Blob;
    return p->n ? p->z : 0;
  }else{
    return sqlite3_value_text(pVal);
  }
}