#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* z; int n; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 char* TS_PATH_DELIMITER ; 
 char* strnchr (char*,char const,int,int) ; 

void extractTableNameFromToken(SSQLToken* pToken, SSQLToken* pTable) {
  const char sep = TS_PATH_DELIMITER[0];

  if (pToken == pTable || pToken == NULL || pTable == NULL) {
    return;
  }

  char* r = strnchr(pToken->z, sep, pToken->n, false);

  if (r != NULL) {  // record the table name token
    pTable->n = r - pToken->z;
    pTable->z = pToken->z;

    r += 1;
    pToken->n -= (r - pToken->z);
    pToken->z = r;
  }
}