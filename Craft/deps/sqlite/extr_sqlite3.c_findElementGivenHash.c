#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct _ht {int count; TYPE_1__* chain; } ;
struct TYPE_7__ {int count; TYPE_1__* first; struct _ht* ht; } ;
struct TYPE_6__ {int nKey; struct TYPE_6__* next; int /*<<< orphan*/  pKey; } ;
typedef  TYPE_1__ HashElem ;
typedef  TYPE_2__ Hash ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_1__*) ; 
 scalar_t__ sqlite3StrNICmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static HashElem *findElementGivenHash(
  const Hash *pH,     /* The pH to be searched */
  const char *pKey,   /* The key we are searching for */
  int nKey,           /* Bytes in key (not counting zero terminator) */
  unsigned int h      /* The hash for this key. */
){
  HashElem *elem;                /* Used to loop thru the element list */
  int count;                     /* Number of elements left to test */

  if( pH->ht ){
    struct _ht *pEntry = &pH->ht[h];
    elem = pEntry->chain;
    count = pEntry->count;
  }else{
    elem = pH->first;
    count = pH->count;
  }
  while( count-- && ALWAYS(elem) ){
    if( elem->nKey==nKey && sqlite3StrNICmp(elem->pKey,pKey,nKey)==0 ){ 
      return elem;
    }
    elem = elem->next;
  }
  return 0;
}