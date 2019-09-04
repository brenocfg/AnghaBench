#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ssl; int /*<<< orphan*/ * ssl_ctx; } ;
typedef  TYPE_1__ ws_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 scalar_t__ SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SSL_CTX_use_certificate_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_accept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_fd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLSv1_server_method () ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int ssl_initialized ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ws_socket (TYPE_1__*,int) ; 

ws_ctx_t *ws_socket_ssl(ws_ctx_t *ctx, int socket, char * certfile, char * keyfile) {
    int ret;
    char msg[1024];
    char * use_keyfile;
    ws_socket(ctx, socket);

    if (keyfile && (keyfile[0] != '\0')) {
        // Separate key file
        use_keyfile = keyfile;
    } else {
        // Combined key and cert file
        use_keyfile = certfile;
    }

    // Initialize the library
    if (! ssl_initialized) {
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
        ssl_initialized = 1;

    }

    ctx->ssl_ctx = SSL_CTX_new(TLSv1_server_method());
    if (ctx->ssl_ctx == NULL) {
        ERR_print_errors_fp(stderr);
        fatal("Failed to configure SSL context");
    }

    if (SSL_CTX_use_PrivateKey_file(ctx->ssl_ctx, use_keyfile,
                                    SSL_FILETYPE_PEM) <= 0) {
        sprintf(msg, "Unable to load private key file %s\n", use_keyfile);
        fatal(msg);
    }

    if (SSL_CTX_use_certificate_file(ctx->ssl_ctx, certfile,
                                     SSL_FILETYPE_PEM) <= 0) {
        sprintf(msg, "Unable to load certificate file %s\n", certfile);
        fatal(msg);
    }

//    if (SSL_CTX_set_cipher_list(ctx->ssl_ctx, "DEFAULT") != 1) {
//        sprintf(msg, "Unable to set cipher\n");
//        fatal(msg);
//    }

    // Associate socket and ssl object
    ctx->ssl = SSL_new(ctx->ssl_ctx);
    SSL_set_fd(ctx->ssl, socket);

    ret = SSL_accept(ctx->ssl);
    if (ret < 0) {
        ERR_print_errors_fp(stderr);
        return NULL;
    }

    return ctx;
}