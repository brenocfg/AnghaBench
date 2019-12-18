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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  pass; } ;
typedef  TYPE_1__ SUserObj ;

/* Variables and functions */
 int TSDB_CODE_INVALID_USER ; 
 int /*<<< orphan*/  TSDB_KEY_LEN ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mgmtGetUser (char*) ; 

int mgmtRetriveUserAuthInfo(char *user, char *spi, char *encrypt, uint8_t *secret, uint8_t *ckey) {
  SUserObj *pUser = NULL;

  *spi = 0;
  *encrypt = 0;
  secret[0] = 0;
  ckey[0] = 0;

  pUser = mgmtGetUser(user);
  if (pUser == NULL) return TSDB_CODE_INVALID_USER;

  *spi = 1;
  *encrypt = 0;
  memcpy(secret, pUser->pass, TSDB_KEY_LEN);

  return 0;
}