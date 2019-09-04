#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; TYPE_6__* header; } ;
typedef  TYPE_3__ WU_WEBPAGE ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_36__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_35__ {int WasSstp; TYPE_4__* FirstSock; TYPE_1__* Cedar; void* Err; int /*<<< orphan*/  Type; } ;
struct TYPE_34__ {int /*<<< orphan*/  Target; int /*<<< orphan*/  Version; int /*<<< orphan*/  Method; } ;
struct TYPE_33__ {int DisableSSTPServer; scalar_t__ UseWebUI; } ;
struct TYPE_30__ {int* addr; } ;
struct TYPE_32__ {TYPE_2__ RemoteIP; scalar_t__ IsReverseAcceptedSocket; int /*<<< orphan*/  SecureMode; } ;
struct TYPE_29__ {int /*<<< orphan*/  WebUI; TYPE_5__* Server; } ;
typedef  TYPE_4__ SOCK ;
typedef  TYPE_5__ SERVER ;
typedef  TYPE_6__ HTTP_HEADER ;
typedef  TYPE_7__ CONNECTION ;
typedef  TYPE_8__ BUF ;

/* Variables and functions */
 int AcceptSstp (TYPE_7__*) ; 
 int /*<<< orphan*/  AddHttpValue (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTION_TYPE_SSTP ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Disconnect (TYPE_4__*) ; 
 void* ERR_CLIENT_IS_NOT_VPN ; 
 void* ERR_DISCONNECTED ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_8__*) ; 
 int /*<<< orphan*/  FreeHttpHeader (TYPE_6__*) ; 
 scalar_t__ GetContentLength (TYPE_6__*) ; 
 int GetNoSstp () ; 
 scalar_t__ GetServerCapsBool (TYPE_5__*,char*) ; 
 char* HTTP_CONTENT_TYPE3 ; 
 char* HTTP_CONTENT_TYPE5 ; 
 char* HTTP_KEEP_ALIVE ; 
 int /*<<< orphan*/  HTTP_PICTURES ; 
 char* HTTP_SAITAMA ; 
 char* HTTP_VPN_TARGET2 ; 
 int /*<<< orphan*/  HTTP_VPN_TARGET_POSTDATA ; 
 int /*<<< orphan*/  HttpSendForbidden (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HttpSendNotFound (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HttpSendNotImplemented (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_WATERMARK_SIZE ; 
 int /*<<< orphan*/ * Malloc (scalar_t__) ; 
 TYPE_6__* NewHttpHeader (char*,char*,char*) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 int /*<<< orphan*/  PostHttp (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* ReadDump (char*) ; 
 int RecvAll (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_6__* RecvHttpHeader (TYPE_4__*) ; 
 char* SSTP_URI ; 
 int /*<<< orphan*/  Saitama ; 
 int /*<<< orphan*/  SizeOfSaitama () ; 
 scalar_t__ SizeOfWaterMark () ; 
 scalar_t__ StartWith (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaterMark ; 
 int /*<<< orphan*/  WuFreeWebPage (TYPE_3__*) ; 
 TYPE_3__* WuGetPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool ServerDownloadSignature(CONNECTION *c, char **error_detail_str)
{
	HTTP_HEADER *h;
	UCHAR *data;
	UINT data_size;
	SOCK *s;
	UINT num = 0, max = 19;
	SERVER *server;
	char *vpn_http_target = HTTP_VPN_TARGET2;
	// Validate arguments
	if (c == NULL)
	{
		return false;
	}

	server = c->Cedar->Server;

	s = c->FirstSock;

	while (true)
	{
		bool not_found_error = false;

		num++;
		if (num > max)
		{
			// Disconnect
			Disconnect(s);
			c->Err = ERR_CLIENT_IS_NOT_VPN;

			*error_detail_str = "HTTP_TOO_MANY_REQUEST";
			return false;
		}
		// Receive a header
		h = RecvHttpHeader(s);
		if (h == NULL)
		{
			c->Err = ERR_CLIENT_IS_NOT_VPN;
			return false;
		}

		// Interpret
		if (StrCmpi(h->Method, "POST") == 0)
		{
			// Receive the data since it's POST
			data_size = GetContentLength(h);
			if ((data_size > MAX_WATERMARK_SIZE || data_size < SizeOfWaterMark()) && (data_size != StrLen(HTTP_VPN_TARGET_POSTDATA)))
			{
				// Data is too large
				HttpSendForbidden(s, h->Target, NULL);
				FreeHttpHeader(h);
				c->Err = ERR_CLIENT_IS_NOT_VPN;
				*error_detail_str = "POST_Recv_TooLong";
				return false;
			}
			data = Malloc(data_size);
			if (RecvAll(s, data, data_size, s->SecureMode) == false)
			{
				// Data reception failure
				Free(data);
				FreeHttpHeader(h);
				c->Err = ERR_DISCONNECTED;
				*error_detail_str = "POST_Recv_Failed";
				return false;
			}
			// Check the Target
			if ((StrCmpi(h->Target, vpn_http_target) != 0) || not_found_error)
			{
				// Target is invalid
				HttpSendNotFound(s, h->Target);
				Free(data);
				FreeHttpHeader(h);
				*error_detail_str = "POST_Target_Wrong";
			}
			else
			{
				// Compare posted data with the WaterMark
				if ((data_size == StrLen(HTTP_VPN_TARGET_POSTDATA) && (Cmp(data, HTTP_VPN_TARGET_POSTDATA, data_size) == 0))
					|| ((data_size >= SizeOfWaterMark()) && Cmp(data, WaterMark, SizeOfWaterMark()) == 0))
				{
					// Check the WaterMark
					Free(data);
					FreeHttpHeader(h);
					return true;
				}
				else
				{
					// WaterMark is incorrect
					HttpSendForbidden(s, h->Target, NULL);
					FreeHttpHeader(h);
					*error_detail_str = "POST_WaterMark_Error";
				}
			}
		}
		else if (StrCmpi(h->Method, "SSTP_DUPLEX_POST") == 0 && (server->DisableSSTPServer == false || s->IsReverseAcceptedSocket
			) &&
			GetServerCapsBool(server, "b_support_sstp") && GetNoSstp() == false)
		{
			// SSTP client is connected
			c->WasSstp = true;

			if (StrCmpi(h->Target, SSTP_URI) == 0)
			{
				bool sstp_ret;
				// Accept the SSTP connection
				c->Type = CONNECTION_TYPE_SSTP;

				sstp_ret = AcceptSstp(c);

				c->Err = ERR_DISCONNECTED;
				FreeHttpHeader(h);

				if (sstp_ret)
				{
					*error_detail_str = "";
				}
				else
				{
					*error_detail_str = "SSTP_ABORT";
				}

				return false;
			}
			else
			{
				// URI is invalid
				HttpSendNotFound(s, h->Target);
				*error_detail_str = "SSTP_URL_WRONG";
			}

			FreeHttpHeader(h);
		}
		else
		{
			// This should not be a VPN client, but interpret a bit more
			if (StrCmpi(h->Method, "GET") != 0 && StrCmpi(h->Method, "HEAD") != 0
				 && StrCmpi(h->Method, "POST") != 0)
			{
				// Unsupported method calls
				HttpSendNotImplemented(s, h->Method, h->Target, h->Version);
				*error_detail_str = "HTTP_BAD_METHOD";
			}
			else
			{

				if (StrCmpi(h->Target, "/") == 0)
				{
					// Root directory
					*error_detail_str = "HTTP_ROOT";

					{
						// Other than free version
						HttpSendForbidden(c->FirstSock, h->Target, "");
					}
				}
				else
				{
					bool b = false;

					// Show the WebUI if the configuration allow to use the WebUI
					if (c->Cedar->Server != NULL && c->Cedar->Server->UseWebUI)
					{
						WU_WEBPAGE *page;

						// Show the WebUI
						page = WuGetPage(h->Target, c->Cedar->WebUI);

						if (page != NULL)
						{
							PostHttp(s, page->header, page->data, page->size);
							b = true;
							WuFreeWebPage(page);
						}

					}

					if (c->FirstSock->RemoteIP.addr[0] == 127)
					{
						if (StrCmpi(h->Target, HTTP_SAITAMA) == 0)
						{
							// Saitama (joke)
							FreeHttpHeader(h);
							h = NewHttpHeader("HTTP/1.1", "202", "OK");
							AddHttpValue(h, NewHttpValue("Content-Type", HTTP_CONTENT_TYPE3));
							AddHttpValue(h, NewHttpValue("Connection", "Keep-Alive"));
							AddHttpValue(h, NewHttpValue("Keep-Alive", HTTP_KEEP_ALIVE));
							PostHttp(s, h, Saitama, SizeOfSaitama());
							b = true;
						}
						else if (StartWith(h->Target, HTTP_PICTURES))
						{
							BUF *buf;

							// Lots of photos
							buf = ReadDump("|Pictures.mht");

							if (buf != NULL)
							{
								FreeHttpHeader(h);
								h = NewHttpHeader("HTTP/1.1", "202", "OK");
								AddHttpValue(h, NewHttpValue("Content-Type", HTTP_CONTENT_TYPE5));
								AddHttpValue(h, NewHttpValue("Connection", "Keep-Alive"));
								AddHttpValue(h, NewHttpValue("Keep-Alive", HTTP_KEEP_ALIVE));
								PostHttp(s, h, buf->Buf, buf->Size);
								b = true;

								FreeBuf(buf);
							}
						}
					}

					if (b == false)
					{
						// Not Found
						HttpSendNotFound(s, h->Target);

						*error_detail_str = "HTTP_NOT_FOUND";
					}
				}
			}
			FreeHttpHeader(h);
		}
	}
}