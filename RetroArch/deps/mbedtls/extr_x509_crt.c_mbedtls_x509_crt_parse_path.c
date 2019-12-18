#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szDir ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
struct TYPE_4__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  char WCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ ERROR_NO_MORE_FILES ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (char*,TYPE_1__*) ; 
 scalar_t__ FindNextFileW (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int MBEDTLS_ERR_THREADING_MUTEX_ERROR ; 
 int MBEDTLS_ERR_X509_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_X509_BUFFER_TOO_SMALL ; 
 int MBEDTLS_ERR_X509_FILE_IO_ERROR ; 
 int MBEDTLS_X509_MAX_FILE_PATH_LEN ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/ ) ; 
 int mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 int mbedtls_snprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_threading_readdir_mutex ; 
 int mbedtls_x509_crt_parse_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int stat (char*,struct stat*) ; 
 size_t strlen (char const*) ; 

int mbedtls_x509_crt_parse_path( mbedtls_x509_crt *chain, const char *path )
{
    int ret = 0;
#if defined(_WIN32) && !defined(EFIX64) && !defined(EFI32)
    int w_ret;
    WCHAR szDir[MAX_PATH];
    char filename[MAX_PATH];
    char *p;
    size_t len = strlen( path );

    WIN32_FIND_DATAW file_data;
    HANDLE hFind;

    if( len > MAX_PATH - 3 )
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );

    memset( szDir, 0, sizeof(szDir) );
    memset( filename, 0, MAX_PATH );
    memcpy( filename, path, len );
    filename[len++] = '\\';
    p = filename + len;
    filename[len++] = '*';

    w_ret = MultiByteToWideChar( CP_ACP, 0, filename, (int)len, szDir,
                                 MAX_PATH - 3 );
    if( w_ret == 0 )
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );

    hFind = FindFirstFileW( szDir, &file_data );
    if( hFind == INVALID_HANDLE_VALUE )
        return( MBEDTLS_ERR_X509_FILE_IO_ERROR );

    len = MAX_PATH - len;
    do
    {
        memset( p, 0, len );

        if( file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            continue;

        w_ret = WideCharToMultiByte( CP_ACP, 0, file_data.cFileName,
                                     lstrlenW( file_data.cFileName ),
                                     p, (int) len - 1,
                                     NULL, NULL );
        if( w_ret == 0 )
        {
            ret = MBEDTLS_ERR_X509_FILE_IO_ERROR;
            goto cleanup;
        }

        w_ret = mbedtls_x509_crt_parse_file( chain, filename );
        if( w_ret < 0 )
            ret++;
        else
            ret += w_ret;
    }
    while( FindNextFileW( hFind, &file_data ) != 0 );

    if( GetLastError() != ERROR_NO_MORE_FILES )
        ret = MBEDTLS_ERR_X509_FILE_IO_ERROR;

cleanup:
    FindClose( hFind );
#else /* _WIN32 */
    int t_ret;
    int snp_ret;
    struct stat sb;
    struct dirent *entry;
    char entry_name[MBEDTLS_X509_MAX_FILE_PATH_LEN];
    DIR *dir = opendir( path );

    if( dir == NULL )
        return( MBEDTLS_ERR_X509_FILE_IO_ERROR );

#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &mbedtls_threading_readdir_mutex ) ) != 0 )
    {
        closedir( dir );
        return( ret );
    }
#endif /* MBEDTLS_THREADING_C */

    while( ( entry = readdir( dir ) ) != NULL )
    {
        snp_ret = mbedtls_snprintf( entry_name, sizeof entry_name,
                                    "%s/%s", path, entry->d_name );

        if( snp_ret < 0 || (size_t)snp_ret >= sizeof entry_name )
        {
            ret = MBEDTLS_ERR_X509_BUFFER_TOO_SMALL;
            goto cleanup;
        }
        else if( stat( entry_name, &sb ) == -1 )
        {
            ret = MBEDTLS_ERR_X509_FILE_IO_ERROR;
            goto cleanup;
        }

        if( !S_ISREG( sb.st_mode ) )
            continue;

        /* Ignore parse errors */
        t_ret = mbedtls_x509_crt_parse_file( chain, entry_name );
        if( t_ret < 0 )
            ret++;
        else
            ret += t_ret;
    }

cleanup:
    closedir( dir );

#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &mbedtls_threading_readdir_mutex ) != 0 )
        ret = MBEDTLS_ERR_THREADING_MUTEX_ERROR;
#endif /* MBEDTLS_THREADING_C */

#endif /* _WIN32 */

    return( ret );
}