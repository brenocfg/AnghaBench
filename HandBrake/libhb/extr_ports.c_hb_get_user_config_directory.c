void hb_get_user_config_directory( char path[512] )
{
    /* Create the base */
#if defined( SYS_CYGWIN ) || defined( SYS_MINGW )
#ifndef CSIDL_FLAG_DONT_UNEXPAND
    /*
     * XXX: some old MinGW toolchains don't have SHGetKnownFolderPath.
     *
     * SHGetFolderPath is deprecated, but this should be no problem in practice.
     *
     * Note: explicitly call the Unicode/WCHAR function SHGetFolderPathW.
     */
    WCHAR wide_path[MAX_PATH];

    if (SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, wide_path) == S_OK &&
        WideCharToMultiByte(CP_UTF8, 0, wide_path, -1, path, 512, NULL, NULL) != 0)
    {
        path[511] = 0;
        return;
    }
#else
    WCHAR *wide_path;

    if (SHGetKnownFolderPath(&FOLDERID_RoamingAppData, 0, NULL, &wide_path) == S_OK &&
        WideCharToMultiByte(CP_UTF8, 0, wide_path, -1, path, 512, NULL, NULL) != 0)
    {
        CoTaskMemFree(wide_path);
        path[511] = 0;
        return;
    }
    else if (wide_path != NULL)
    {
        CoTaskMemFree(wide_path);
    }
#endif // !defined CSIDL_FLAG_DONT_UNEXPAND
#elif defined( SYS_LINUX )
    char *p;

    if ((p = getenv("XDG_CONFIG_HOME")) != NULL)
    {
        strncpy(path, p, 511);
        path[511] = 0;
        return;
    }
    else if ((p = getenv("HOME")) != NULL)
    {
        strncpy(path, p, 511);
        path[511] = 0;
        int len = strlen(path);
        strncpy(path + len, "/.config", 511 - len - 1);
        path[511] = 0;
        return;
    }
#elif defined( __APPLE__ )
    if (macOS_get_user_config_directory(path) == 0)
    {
        return;
    }
#endif

    hb_error("Failed to lookup user config directory!");
    path[0] = 0;
}