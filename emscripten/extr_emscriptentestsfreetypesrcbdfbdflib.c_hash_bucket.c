#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long size; TYPE_2__** table; } ;
typedef  TYPE_1__ hashtable ;
typedef  TYPE_2__* hashnode ;
struct TYPE_6__ {char* key; } ;

/* Variables and functions */
 scalar_t__ ft_strcmp (char const*,char const*) ; 

__attribute__((used)) static hashnode*
  hash_bucket( const char*  key,
               hashtable*   ht )
  {
    const char*    kp  = key;
    unsigned long  res = 0;
    hashnode*      bp  = ht->table, *ndp;


    /* Mocklisp hash function. */
    while ( *kp )
      res = ( res << 5 ) - res + *kp++;

    ndp = bp + ( res % ht->size );
    while ( *ndp )
    {
      kp = (*ndp)->key;
      if ( kp[0] == key[0] && ft_strcmp( kp, key ) == 0 )
        break;
      ndp--;
      if ( ndp < bp )
        ndp = bp + ( ht->size - 1 );
    }

    return ndp;
  }