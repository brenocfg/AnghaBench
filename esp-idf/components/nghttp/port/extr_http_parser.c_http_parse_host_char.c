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
typedef  enum http_host_state { ____Placeholder_http_host_state } http_host_state ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALPHANUM (char const) ; 
 int /*<<< orphan*/  IS_HEX (char const) ; 
 int /*<<< orphan*/  IS_HOST_CHAR (char const) ; 
 int /*<<< orphan*/  IS_NUM (char const) ; 
 int /*<<< orphan*/  IS_USERINFO_CHAR (char const) ; 
#define  s_http_host 138 
 int s_http_host_dead ; 
#define  s_http_host_port 137 
#define  s_http_host_port_start 136 
#define  s_http_host_start 135 
#define  s_http_host_v6 134 
#define  s_http_host_v6_end 133 
#define  s_http_host_v6_start 132 
#define  s_http_host_v6_zone 131 
#define  s_http_host_v6_zone_start 130 
#define  s_http_userinfo 129 
#define  s_http_userinfo_start 128 

__attribute__((used)) static enum http_host_state
http_parse_host_char(enum http_host_state s, const char ch) {
  switch(s) {
    case s_http_userinfo:
    case s_http_userinfo_start:
      if (ch == '@') {
        return s_http_host_start;
      }

      if (IS_USERINFO_CHAR(ch)) {
        return s_http_userinfo;
      }
      break;

    case s_http_host_start:
      if (ch == '[') {
        return s_http_host_v6_start;
      }

      if (IS_HOST_CHAR(ch)) {
        return s_http_host;
      }

      break;

    case s_http_host:
      if (IS_HOST_CHAR(ch)) {
        return s_http_host;
      }

    /* FALLTHROUGH */
    case s_http_host_v6_end:
      if (ch == ':') {
        return s_http_host_port_start;
      }

      break;

    case s_http_host_v6:
      if (ch == ']') {
        return s_http_host_v6_end;
      }

    /* FALLTHROUGH */
    case s_http_host_v6_start:
      if (IS_HEX(ch) || ch == ':' || ch == '.') {
        return s_http_host_v6;
      }

      if (s == s_http_host_v6 && ch == '%') {
        return s_http_host_v6_zone_start;
      }
      break;

    case s_http_host_v6_zone:
      if (ch == ']') {
        return s_http_host_v6_end;
      }

    /* FALLTHROUGH */
    case s_http_host_v6_zone_start:
      /* RFC 6874 Zone ID consists of 1*( unreserved / pct-encoded) */
      if (IS_ALPHANUM(ch) || ch == '%' || ch == '.' || ch == '-' || ch == '_' ||
          ch == '~') {
        return s_http_host_v6_zone;
      }
      break;

    case s_http_host_port:
    case s_http_host_port_start:
      if (IS_NUM(ch)) {
        return s_http_host_port;
      }

      break;

    default:
      break;
  }
  return s_http_host_dead;
}