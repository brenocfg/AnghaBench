#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char uint32_t ;
typedef  int /*<<< orphan*/  timeStamp ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {char msgType; char* meterId; int /*<<< orphan*/  msgLen; scalar_t__ content; scalar_t__ sourceId; scalar_t__ destId; int /*<<< orphan*/  tranId; scalar_t__ encrypt; scalar_t__ spi; scalar_t__ tcp; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ STaosHeader ;

/* Variables and functions */
 int TSDB_CODE_INVALID_TIME_STAMP ; 
 scalar_t__ htonl (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int tListLen (char*) ; 
 char taosGetTimestampSec () ; 

int taosBuildErrorMsgToPeer(char *pMsg, int code, char *pReply) {
  STaosHeader *pRecvHeader, *pReplyHeader;
  char *       pContent;
  uint32_t     timeStamp;
  int          msgLen;

  pRecvHeader = (STaosHeader *)pMsg;
  pReplyHeader = (STaosHeader *)pReply;

  pReplyHeader->version = pRecvHeader->version;
  pReplyHeader->msgType = (char)(pRecvHeader->msgType + 1);
  pReplyHeader->tcp = 0;
  pReplyHeader->spi = 0;
  pReplyHeader->encrypt = 0;
  pReplyHeader->tranId = pRecvHeader->tranId;
  pReplyHeader->sourceId = 0;
  pReplyHeader->destId = pRecvHeader->sourceId;
  memcpy(pReplyHeader->meterId, pRecvHeader->meterId, tListLen(pReplyHeader->meterId));

  pContent = (char *)pReplyHeader->content;
  *pContent = (char)code;
  pContent++;

  if (code == TSDB_CODE_INVALID_TIME_STAMP) {
    // include a time stamp if client's time is not synchronized well
    timeStamp = taosGetTimestampSec();
    memcpy(pContent, &timeStamp, sizeof(timeStamp));
    pContent += sizeof(timeStamp);
  }

  msgLen = (int)(pContent - pReply);
  pReplyHeader->msgLen = (int32_t)htonl((uint32_t)msgLen);

  return msgLen;
}