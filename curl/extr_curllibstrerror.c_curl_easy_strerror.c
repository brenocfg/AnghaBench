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
typedef  int CURLcode ;

/* Variables and functions */
#define  CURLE_ABORTED_BY_CALLBACK 222 
#define  CURLE_AGAIN 221 
#define  CURLE_BAD_CONTENT_ENCODING 220 
#define  CURLE_BAD_DOWNLOAD_RESUME 219 
#define  CURLE_BAD_FUNCTION_ARGUMENT 218 
#define  CURLE_CHUNK_FAILED 217 
#define  CURLE_CONV_FAILED 216 
#define  CURLE_CONV_REQD 215 
#define  CURLE_COULDNT_CONNECT 214 
#define  CURLE_COULDNT_RESOLVE_HOST 213 
#define  CURLE_COULDNT_RESOLVE_PROXY 212 
#define  CURLE_FAILED_INIT 211 
#define  CURLE_FILESIZE_EXCEEDED 210 
#define  CURLE_FILE_COULDNT_READ_FILE 209 
#define  CURLE_FTP_ACCEPT_FAILED 208 
#define  CURLE_FTP_ACCEPT_TIMEOUT 207 
#define  CURLE_FTP_BAD_FILE_LIST 206 
#define  CURLE_FTP_CANT_GET_HOST 205 
#define  CURLE_FTP_COULDNT_RETR_FILE 204 
#define  CURLE_FTP_COULDNT_SET_TYPE 203 
#define  CURLE_FTP_COULDNT_USE_REST 202 
#define  CURLE_FTP_PORT_FAILED 201 
#define  CURLE_FTP_PRET_FAILED 200 
#define  CURLE_FTP_WEIRD_227_FORMAT 199 
#define  CURLE_FTP_WEIRD_PASS_REPLY 198 
#define  CURLE_FTP_WEIRD_PASV_REPLY 197 
#define  CURLE_FUNCTION_NOT_FOUND 196 
#define  CURLE_GOT_NOTHING 195 
#define  CURLE_HTTP2 194 
#define  CURLE_HTTP2_STREAM 193 
#define  CURLE_HTTP_POST_ERROR 192 
#define  CURLE_HTTP_RETURNED_ERROR 191 
#define  CURLE_INTERFACE_FAILED 190 
#define  CURLE_LDAP_CANNOT_BIND 189 
#define  CURLE_LDAP_INVALID_URL 188 
#define  CURLE_LDAP_SEARCH_FAILED 187 
#define  CURLE_LOGIN_DENIED 186 
#define  CURLE_NOT_BUILT_IN 185 
#define  CURLE_NO_CONNECTION_AVAILABLE 184 
#define  CURLE_OBSOLETE20 183 
#define  CURLE_OBSOLETE24 182 
#define  CURLE_OBSOLETE29 181 
#define  CURLE_OBSOLETE32 180 
#define  CURLE_OBSOLETE40 179 
#define  CURLE_OBSOLETE44 178 
#define  CURLE_OBSOLETE46 177 
#define  CURLE_OBSOLETE50 176 
#define  CURLE_OBSOLETE51 175 
#define  CURLE_OBSOLETE57 174 
#define  CURLE_OK 173 
#define  CURLE_OPERATION_TIMEDOUT 172 
#define  CURLE_OUT_OF_MEMORY 171 
#define  CURLE_PARTIAL_FILE 170 
#define  CURLE_PEER_FAILED_VERIFICATION 169 
#define  CURLE_QUOTE_ERROR 168 
#define  CURLE_RANGE_ERROR 167 
#define  CURLE_READ_ERROR 166 
#define  CURLE_RECURSIVE_API_CALL 165 
#define  CURLE_RECV_ERROR 164 
#define  CURLE_REMOTE_ACCESS_DENIED 163 
#define  CURLE_REMOTE_DISK_FULL 162 
#define  CURLE_REMOTE_FILE_EXISTS 161 
#define  CURLE_REMOTE_FILE_NOT_FOUND 160 
#define  CURLE_RTSP_CSEQ_ERROR 159 
#define  CURLE_RTSP_SESSION_ERROR 158 
#define  CURLE_SEND_ERROR 157 
#define  CURLE_SEND_FAIL_REWIND 156 
#define  CURLE_SSH 155 
#define  CURLE_SSL_CACERT_BADFILE 154 
#define  CURLE_SSL_CERTPROBLEM 153 
#define  CURLE_SSL_CIPHER 152 
#define  CURLE_SSL_CONNECT_ERROR 151 
#define  CURLE_SSL_CRL_BADFILE 150 
#define  CURLE_SSL_ENGINE_INITFAILED 149 
#define  CURLE_SSL_ENGINE_NOTFOUND 148 
#define  CURLE_SSL_ENGINE_SETFAILED 147 
#define  CURLE_SSL_INVALIDCERTSTATUS 146 
#define  CURLE_SSL_ISSUER_ERROR 145 
#define  CURLE_SSL_PINNEDPUBKEYNOTMATCH 144 
#define  CURLE_SSL_SHUTDOWN_FAILED 143 
#define  CURLE_TELNET_OPTION_SYNTAX 142 
#define  CURLE_TFTP_ILLEGAL 141 
#define  CURLE_TFTP_NOSUCHUSER 140 
#define  CURLE_TFTP_NOTFOUND 139 
#define  CURLE_TFTP_PERM 138 
#define  CURLE_TFTP_UNKNOWNID 137 
#define  CURLE_TOO_MANY_REDIRECTS 136 
#define  CURLE_UNKNOWN_OPTION 135 
#define  CURLE_UNSUPPORTED_PROTOCOL 134 
#define  CURLE_UPLOAD_FAILED 133 
#define  CURLE_URL_MALFORMAT 132 
#define  CURLE_USE_SSL_FAILED 131 
#define  CURLE_WEIRD_SERVER_REPLY 130 
#define  CURLE_WRITE_ERROR 129 
#define  CURL_LAST 128 

const char *
curl_easy_strerror(CURLcode error)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch(error) {
  case CURLE_OK:
    return "No error";

  case CURLE_UNSUPPORTED_PROTOCOL:
    return "Unsupported protocol";

  case CURLE_FAILED_INIT:
    return "Failed initialization";

  case CURLE_URL_MALFORMAT:
    return "URL using bad/illegal format or missing URL";

  case CURLE_NOT_BUILT_IN:
    return "A requested feature, protocol or option was not found built-in in"
      " this libcurl due to a build-time decision.";

  case CURLE_COULDNT_RESOLVE_PROXY:
    return "Couldn't resolve proxy name";

  case CURLE_COULDNT_RESOLVE_HOST:
    return "Couldn't resolve host name";

  case CURLE_COULDNT_CONNECT:
    return "Couldn't connect to server";

  case CURLE_WEIRD_SERVER_REPLY:
    return "Weird server reply";

  case CURLE_REMOTE_ACCESS_DENIED:
    return "Access denied to remote resource";

  case CURLE_FTP_ACCEPT_FAILED:
    return "FTP: The server failed to connect to data port";

  case CURLE_FTP_ACCEPT_TIMEOUT:
    return "FTP: Accepting server connect has timed out";

  case CURLE_FTP_PRET_FAILED:
    return "FTP: The server did not accept the PRET command.";

  case CURLE_FTP_WEIRD_PASS_REPLY:
    return "FTP: unknown PASS reply";

  case CURLE_FTP_WEIRD_PASV_REPLY:
    return "FTP: unknown PASV reply";

  case CURLE_FTP_WEIRD_227_FORMAT:
    return "FTP: unknown 227 response format";

  case CURLE_FTP_CANT_GET_HOST:
    return "FTP: can't figure out the host in the PASV response";

  case CURLE_HTTP2:
    return "Error in the HTTP2 framing layer";

  case CURLE_FTP_COULDNT_SET_TYPE:
    return "FTP: couldn't set file type";

  case CURLE_PARTIAL_FILE:
    return "Transferred a partial file";

  case CURLE_FTP_COULDNT_RETR_FILE:
    return "FTP: couldn't retrieve (RETR failed) the specified file";

  case CURLE_QUOTE_ERROR:
    return "Quote command returned error";

  case CURLE_HTTP_RETURNED_ERROR:
    return "HTTP response code said error";

  case CURLE_WRITE_ERROR:
    return "Failed writing received data to disk/application";

  case CURLE_UPLOAD_FAILED:
    return "Upload failed (at start/before it took off)";

  case CURLE_READ_ERROR:
    return "Failed to open/read local data from file/application";

  case CURLE_OUT_OF_MEMORY:
    return "Out of memory";

  case CURLE_OPERATION_TIMEDOUT:
    return "Timeout was reached";

  case CURLE_FTP_PORT_FAILED:
    return "FTP: command PORT failed";

  case CURLE_FTP_COULDNT_USE_REST:
    return "FTP: command REST failed";

  case CURLE_RANGE_ERROR:
    return "Requested range was not delivered by the server";

  case CURLE_HTTP_POST_ERROR:
    return "Internal problem setting up the POST";

  case CURLE_SSL_CONNECT_ERROR:
    return "SSL connect error";

  case CURLE_BAD_DOWNLOAD_RESUME:
    return "Couldn't resume download";

  case CURLE_FILE_COULDNT_READ_FILE:
    return "Couldn't read a file:// file";

  case CURLE_LDAP_CANNOT_BIND:
    return "LDAP: cannot bind";

  case CURLE_LDAP_SEARCH_FAILED:
    return "LDAP: search failed";

  case CURLE_FUNCTION_NOT_FOUND:
    return "A required function in the library was not found";

  case CURLE_ABORTED_BY_CALLBACK:
    return "Operation was aborted by an application callback";

  case CURLE_BAD_FUNCTION_ARGUMENT:
    return "A libcurl function was given a bad argument";

  case CURLE_INTERFACE_FAILED:
    return "Failed binding local connection end";

  case CURLE_TOO_MANY_REDIRECTS :
    return "Number of redirects hit maximum amount";

  case CURLE_UNKNOWN_OPTION:
    return "An unknown option was passed in to libcurl";

  case CURLE_TELNET_OPTION_SYNTAX :
    return "Malformed telnet option";

  case CURLE_GOT_NOTHING:
    return "Server returned nothing (no headers, no data)";

  case CURLE_SSL_ENGINE_NOTFOUND:
    return "SSL crypto engine not found";

  case CURLE_SSL_ENGINE_SETFAILED:
    return "Can not set SSL crypto engine as default";

  case CURLE_SSL_ENGINE_INITFAILED:
    return "Failed to initialise SSL crypto engine";

  case CURLE_SEND_ERROR:
    return "Failed sending data to the peer";

  case CURLE_RECV_ERROR:
    return "Failure when receiving data from the peer";

  case CURLE_SSL_CERTPROBLEM:
    return "Problem with the local SSL certificate";

  case CURLE_SSL_CIPHER:
    return "Couldn't use specified SSL cipher";

  case CURLE_PEER_FAILED_VERIFICATION:
    return "SSL peer certificate or SSH remote key was not OK";

  case CURLE_SSL_CACERT_BADFILE:
    return "Problem with the SSL CA cert (path? access rights?)";

  case CURLE_BAD_CONTENT_ENCODING:
    return "Unrecognized or bad HTTP Content or Transfer-Encoding";

  case CURLE_LDAP_INVALID_URL:
    return "Invalid LDAP URL";

  case CURLE_FILESIZE_EXCEEDED:
    return "Maximum file size exceeded";

  case CURLE_USE_SSL_FAILED:
    return "Requested SSL level failed";

  case CURLE_SSL_SHUTDOWN_FAILED:
    return "Failed to shut down the SSL connection";

  case CURLE_SSL_CRL_BADFILE:
    return "Failed to load CRL file (path? access rights?, format?)";

  case CURLE_SSL_ISSUER_ERROR:
    return "Issuer check against peer certificate failed";

  case CURLE_SEND_FAIL_REWIND:
    return "Send failed since rewinding of the data stream failed";

  case CURLE_LOGIN_DENIED:
    return "Login denied";

  case CURLE_TFTP_NOTFOUND:
    return "TFTP: File Not Found";

  case CURLE_TFTP_PERM:
    return "TFTP: Access Violation";

  case CURLE_REMOTE_DISK_FULL:
    return "Disk full or allocation exceeded";

  case CURLE_TFTP_ILLEGAL:
    return "TFTP: Illegal operation";

  case CURLE_TFTP_UNKNOWNID:
    return "TFTP: Unknown transfer ID";

  case CURLE_REMOTE_FILE_EXISTS:
    return "Remote file already exists";

  case CURLE_TFTP_NOSUCHUSER:
    return "TFTP: No such user";

  case CURLE_CONV_FAILED:
    return "Conversion failed";

  case CURLE_CONV_REQD:
    return "Caller must register CURLOPT_CONV_ callback options";

  case CURLE_REMOTE_FILE_NOT_FOUND:
    return "Remote file not found";

  case CURLE_SSH:
    return "Error in the SSH layer";

  case CURLE_AGAIN:
    return "Socket not ready for send/recv";

  case CURLE_RTSP_CSEQ_ERROR:
    return "RTSP CSeq mismatch or invalid CSeq";

  case CURLE_RTSP_SESSION_ERROR:
    return "RTSP session error";

  case CURLE_FTP_BAD_FILE_LIST:
    return "Unable to parse FTP file list";

  case CURLE_CHUNK_FAILED:
    return "Chunk callback failed";

  case CURLE_NO_CONNECTION_AVAILABLE:
    return "The max connection limit is reached";

  case CURLE_SSL_PINNEDPUBKEYNOTMATCH:
    return "SSL public key does not match pinned public key";

  case CURLE_SSL_INVALIDCERTSTATUS:
    return "SSL server certificate status verification FAILED";

  case CURLE_HTTP2_STREAM:
    return "Stream error in the HTTP/2 framing layer";

  case CURLE_RECURSIVE_API_CALL:
    return "API function called from within callback";

    /* error codes not used by current libcurl */
  case CURLE_OBSOLETE20:
  case CURLE_OBSOLETE24:
  case CURLE_OBSOLETE29:
  case CURLE_OBSOLETE32:
  case CURLE_OBSOLETE40:
  case CURLE_OBSOLETE44:
  case CURLE_OBSOLETE46:
  case CURLE_OBSOLETE50:
  case CURLE_OBSOLETE51:
  case CURLE_OBSOLETE57:
  case CURL_LAST:
    break;
  }
  /*
   * By using a switch, gcc -Wall will complain about enum values
   * which do not appear, helping keep this function up-to-date.
   * By using gcc -Wall -Werror, you can't forget.
   *
   * A table would not have the same benefit.  Most compilers will
   * generate code very similar to a table in any case, so there
   * is little performance gain from a table.  And something is broken
   * for the user's application, anyways, so does it matter how fast
   * it _doesn't_ work?
   *
   * The line number for the error will be near this comment, which
   * is why it is here, and not at the start of the switch.
   */
  return "Unknown error";
#else
  if(!error)
    return "No error";
  else
    return "Error";
#endif
}