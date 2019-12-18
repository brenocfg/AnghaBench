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
typedef  int tftp_error_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_ABORTED_BY_CALLBACK ; 
 int /*<<< orphan*/  CURLE_COULDNT_CONNECT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OPERATION_TIMEDOUT ; 
 int /*<<< orphan*/  CURLE_REMOTE_DISK_FULL ; 
 int /*<<< orphan*/  CURLE_REMOTE_FILE_EXISTS ; 
 int /*<<< orphan*/  CURLE_TFTP_ILLEGAL ; 
 int /*<<< orphan*/  CURLE_TFTP_NOSUCHUSER ; 
 int /*<<< orphan*/  CURLE_TFTP_NOTFOUND ; 
 int /*<<< orphan*/  CURLE_TFTP_PERM ; 
 int /*<<< orphan*/  CURLE_TFTP_UNKNOWNID ; 
#define  TFTP_ERR_DISKFULL 137 
#define  TFTP_ERR_EXISTS 136 
#define  TFTP_ERR_ILLEGAL 135 
 int TFTP_ERR_NONE ; 
#define  TFTP_ERR_NORESPONSE 134 
#define  TFTP_ERR_NOSUCHUSER 133 
#define  TFTP_ERR_NOTFOUND 132 
#define  TFTP_ERR_PERM 131 
#define  TFTP_ERR_TIMEOUT 130 
#define  TFTP_ERR_UNDEF 129 
#define  TFTP_ERR_UNKNOWNID 128 

__attribute__((used)) static CURLcode tftp_translate_code(tftp_error_t error)
{
  CURLcode result = CURLE_OK;

  if(error != TFTP_ERR_NONE) {
    switch(error) {
    case TFTP_ERR_NOTFOUND:
      result = CURLE_TFTP_NOTFOUND;
      break;
    case TFTP_ERR_PERM:
      result = CURLE_TFTP_PERM;
      break;
    case TFTP_ERR_DISKFULL:
      result = CURLE_REMOTE_DISK_FULL;
      break;
    case TFTP_ERR_UNDEF:
    case TFTP_ERR_ILLEGAL:
      result = CURLE_TFTP_ILLEGAL;
      break;
    case TFTP_ERR_UNKNOWNID:
      result = CURLE_TFTP_UNKNOWNID;
      break;
    case TFTP_ERR_EXISTS:
      result = CURLE_REMOTE_FILE_EXISTS;
      break;
    case TFTP_ERR_NOSUCHUSER:
      result = CURLE_TFTP_NOSUCHUSER;
      break;
    case TFTP_ERR_TIMEOUT:
      result = CURLE_OPERATION_TIMEDOUT;
      break;
    case TFTP_ERR_NORESPONSE:
      result = CURLE_COULDNT_CONNECT;
      break;
    default:
      result = CURLE_ABORTED_BY_CALLBACK;
      break;
    }
  }
  else
    result = CURLE_OK;

  return result;
}