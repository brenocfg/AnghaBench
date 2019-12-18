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
#define  CURLPROTO_DICT 155 
#define  CURLPROTO_FILE 154 
#define  CURLPROTO_FTP 153 
#define  CURLPROTO_FTPS 152 
#define  CURLPROTO_GOPHER 151 
#define  CURLPROTO_HTTP 150 
#define  CURLPROTO_HTTPS 149 
#define  CURLPROTO_IMAP 148 
#define  CURLPROTO_IMAPS 147 
#define  CURLPROTO_LDAP 146 
#define  CURLPROTO_LDAPS 145 
#define  CURLPROTO_POP3 144 
#define  CURLPROTO_POP3S 143 
#define  CURLPROTO_RTMP 142 
#define  CURLPROTO_RTMPE 141 
#define  CURLPROTO_RTMPS 140 
#define  CURLPROTO_RTMPT 139 
#define  CURLPROTO_RTMPTE 138 
#define  CURLPROTO_RTMPTS 137 
#define  CURLPROTO_RTSP 136 
#define  CURLPROTO_SCP 135 
#define  CURLPROTO_SFTP 134 
#define  CURLPROTO_SMB 133 
#define  CURLPROTO_SMBS 132 
#define  CURLPROTO_SMTP 131 
#define  CURLPROTO_SMTPS 130 
#define  CURLPROTO_TELNET 129 
#define  CURLPROTO_TFTP 128 

__attribute__((used)) static unsigned int get_protocol_family(unsigned int protocol)
{
  unsigned int family;

  switch(protocol) {
  case CURLPROTO_HTTP:
  case CURLPROTO_HTTPS:
    family = CURLPROTO_HTTP;
    break;

  case CURLPROTO_FTP:
  case CURLPROTO_FTPS:
    family = CURLPROTO_FTP;
    break;

  case CURLPROTO_SCP:
    family = CURLPROTO_SCP;
    break;

  case CURLPROTO_SFTP:
    family = CURLPROTO_SFTP;
    break;

  case CURLPROTO_TELNET:
    family = CURLPROTO_TELNET;
    break;

  case CURLPROTO_LDAP:
  case CURLPROTO_LDAPS:
    family = CURLPROTO_LDAP;
    break;

  case CURLPROTO_DICT:
    family = CURLPROTO_DICT;
    break;

  case CURLPROTO_FILE:
    family = CURLPROTO_FILE;
    break;

  case CURLPROTO_TFTP:
    family = CURLPROTO_TFTP;
    break;

  case CURLPROTO_IMAP:
  case CURLPROTO_IMAPS:
    family = CURLPROTO_IMAP;
    break;

  case CURLPROTO_POP3:
  case CURLPROTO_POP3S:
    family = CURLPROTO_POP3;
    break;

  case CURLPROTO_SMTP:
  case CURLPROTO_SMTPS:
      family = CURLPROTO_SMTP;
      break;

  case CURLPROTO_RTSP:
    family = CURLPROTO_RTSP;
    break;

  case CURLPROTO_RTMP:
  case CURLPROTO_RTMPS:
    family = CURLPROTO_RTMP;
    break;

  case CURLPROTO_RTMPT:
  case CURLPROTO_RTMPTS:
    family = CURLPROTO_RTMPT;
    break;

  case CURLPROTO_RTMPE:
    family = CURLPROTO_RTMPE;
    break;

  case CURLPROTO_RTMPTE:
    family = CURLPROTO_RTMPTE;
    break;

  case CURLPROTO_GOPHER:
    family = CURLPROTO_GOPHER;
    break;

  case CURLPROTO_SMB:
  case CURLPROTO_SMBS:
    family = CURLPROTO_SMB;
    break;

  default:
      family = 0;
      break;
  }

  return family;
}