#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ n; int /*<<< orphan*/  z; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 int /*<<< orphan*/  TSQL_TBNAME_L ; 
 int /*<<< orphan*/  extractTableNameFromToken (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool isTablenameToken(SSQLToken* token) {
  SSQLToken tmpToken = *token;
  SSQLToken tableToken = {0};

  extractTableNameFromToken(&tmpToken, &tableToken);

  return (strncasecmp(TSQL_TBNAME_L, tmpToken.z, tmpToken.n) == 0 && tmpToken.n == strlen(TSQL_TBNAME_L));
}