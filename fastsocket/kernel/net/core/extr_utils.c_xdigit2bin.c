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
 int IN6PTON_COLON_MASK ; 
 int IN6PTON_DELIM ; 
 char IN6PTON_DIGIT ; 
 int IN6PTON_DOT ; 
 int IN6PTON_UNKNOWN ; 
 char IN6PTON_XDIGIT ; 

__attribute__((used)) static inline int xdigit2bin(char c, int delim)
{
	if (c == delim || c == '\0')
		return IN6PTON_DELIM;
	if (c == ':')
		return IN6PTON_COLON_MASK;
	if (c == '.')
		return IN6PTON_DOT;
	if (c >= '0' && c <= '9')
		return (IN6PTON_XDIGIT | IN6PTON_DIGIT| (c - '0'));
	if (c >= 'a' && c <= 'f')
		return (IN6PTON_XDIGIT | (c - 'a' + 10));
	if (c >= 'A' && c <= 'F')
		return (IN6PTON_XDIGIT | (c - 'A' + 10));
	if (delim == -1)
		return IN6PTON_DELIM;
	return IN6PTON_UNKNOWN;
}