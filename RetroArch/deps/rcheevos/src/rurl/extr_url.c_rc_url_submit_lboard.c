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
typedef  int /*<<< orphan*/  urle_user_name ;
typedef  int /*<<< orphan*/  urle_login_token ;

/* Variables and functions */
 scalar_t__ rc_url_encode (char*,int,char const*) ; 
 int snprintf (char*,size_t,char*,char*,char*,unsigned int,unsigned int,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 

int rc_url_submit_lboard(char* buffer, size_t size, const char* user_name, const char* login_token, unsigned lboard_id, unsigned value, unsigned char hash[16]) {
  char urle_user_name[64];
  char urle_login_token[64];
  int written;

  if (rc_url_encode(urle_user_name, sizeof(urle_user_name), user_name) != 0) {
    return -1;
  }
  
  if (rc_url_encode(urle_login_token, sizeof(urle_login_token), login_token) != 0) {
    return -1;
  }
  
  written = snprintf(
    buffer,
    size,
    "http://retroachievements.org/dorequest.php?r=submitlbentry&u=%s&t=%s&i=%u&s=%u&v=%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
    urle_user_name,
    urle_login_token,
    lboard_id,
    value,
    hash[ 0], hash[ 1], hash[ 2], hash[ 3], hash[ 4], hash[ 5], hash[ 6], hash[ 7],
    hash[ 8], hash[ 9], hash[10], hash[11],hash[12], hash[13], hash[14], hash[15]
  );

  return (size_t)written >= size ? -1 : 0;
}