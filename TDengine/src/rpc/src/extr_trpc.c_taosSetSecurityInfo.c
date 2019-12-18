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

/* Variables and functions */

int taosSetSecurityInfo(int chann, int sid, char *id, int spi, int encrypt, char *secret, char *ckey) {
  /*
    SRpcConn *pConn;

    pConn = connList[chann*tsSessionsPerChann + sid];

    if ( pConn == NULL ) {
      pConn = (SRpcConn *)sizeof(SRpcConn);

      if ( pConn == NULL ) {
        tError("failed to allocate memory for taosConn");
        return -1;
      }

      memset(pConn, 0, sizeof(SRpcConn));
      pConn->chann = chann;
      pConn->sid = sid;
    }

    pConn->spi = spi;
    pConn->encrypt = encrypt;
    memcpy(pConn->secret, pConn->secret, TSDB_KEY_LEN);
    memcpy(pConn->cipheringKey, ckey, TSDB_KEY_LEN);
    memcpy(pConn->meterId, id, TSDB_METER_ID_LEN);
  */
  return -1;
}