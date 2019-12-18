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
typedef  int UINT ;

/* Variables and functions */
 int ERR_CONNECT_FAILED ; 
 int ERR_DISCONNECTED ; 
 int ERR_INTERNAL_ERROR ; 
 int ERR_NO_ERROR ; 
 int ERR_PROXY_AUTH_FAILED ; 
 int ERR_PROXY_CONNECT_FAILED ; 
 int ERR_PROXY_ERROR ; 
 int ERR_USER_CANCEL ; 
#define  PROXY_ERROR_AUTHENTICATION 135 
#define  PROXY_ERROR_CANCELED 134 
#define  PROXY_ERROR_CONNECTION 133 
#define  PROXY_ERROR_DISCONNECTED 132 
#define  PROXY_ERROR_GENERIC 131 
#define  PROXY_ERROR_SUCCESS 130 
#define  PROXY_ERROR_TARGET 129 
#define  PROXY_ERROR_VERSION 128 

UINT ProxyCodeToCedar(UINT code)
{
	switch (code)
	{
	case PROXY_ERROR_SUCCESS:
		return ERR_NO_ERROR;
	case PROXY_ERROR_GENERIC:
	case PROXY_ERROR_VERSION:
		return ERR_PROXY_ERROR;
	case PROXY_ERROR_CANCELED:
		return ERR_USER_CANCEL;
	case PROXY_ERROR_CONNECTION:
		return ERR_PROXY_CONNECT_FAILED;
	case PROXY_ERROR_TARGET:
		return ERR_CONNECT_FAILED;
	case PROXY_ERROR_DISCONNECTED:
		return ERR_DISCONNECTED;
	case PROXY_ERROR_AUTHENTICATION:
		return ERR_PROXY_AUTH_FAILED;
	default:
		return ERR_INTERNAL_ERROR;
	}
}