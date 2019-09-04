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
typedef  int CURLformoption ;

/* Variables and functions */
#define  CURLFORM_BUFFER 134 
#define  CURLFORM_CONTENTTYPE 133 
#define  CURLFORM_COPYCONTENTS 132 
#define  CURLFORM_COPYNAME 131 
#define  CURLFORM_FILE 130 
#define  CURLFORM_FILECONTENT 129 
#define  CURLFORM_FILENAME 128 

__attribute__((used)) static int
Curl_is_formadd_string(CURLformoption option)

{
  switch (option) {

  case CURLFORM_FILENAME:
  case CURLFORM_CONTENTTYPE:
  case CURLFORM_BUFFER:
  case CURLFORM_FILE:
  case CURLFORM_FILECONTENT:
  case CURLFORM_COPYCONTENTS:
  case CURLFORM_COPYNAME:
    return 1;
  }

  return 0;
}