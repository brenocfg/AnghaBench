#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
struct TYPE_7__ {TYPE_1__* pTscObj; } ;
struct TYPE_6__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSQLToken ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void getCurrentDBName(SSqlObj* pSql, SSQLToken* pDBToken) {
  pDBToken->z = pSql->pTscObj->db;
  pDBToken->n = strlen(pSql->pTscObj->db);
}